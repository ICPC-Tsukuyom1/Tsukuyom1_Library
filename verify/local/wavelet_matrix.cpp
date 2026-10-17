#include "../../template.cpp"
#include "../../Structure/wavelet-matrix.cpp"

namespace {
size_t checked_ranges = 0;

void require(bool ok, const char* operation, int n, int l, int r) {
  if (!ok) {
    cerr << "WaveletMatrix regression failed: " << operation << " n=" << n
         << " range=[" << l << ',' << r << ")\n";
    exit(1);
  }
}

template <class T>
vec<T> thresholds(const vec<T>& a) {
  vec<T> result = {numeric_limits<T>::lowest(),
                   numeric_limits<T>::max(),
                   T(-3),
                   T(-2),
                   T(-1),
                   T(0),
                   T(1),
                   T(2),
                   T(3)};
  vec<T> sorted = a;
  sort(all(sorted));
  if (sorted.size() <= 8) {
    result.insert(result.end(), all(sorted));
  } else {
    for (size_t i : {size_t(0), sorted.size() / 4, sorted.size() / 2,
                     sorted.size() * 3 / 4, sorted.size() - 1})
      result.push_back(sorted[i]);
  }
  // Neighbors exercise absent thresholds without overflowing at either extreme.
  const vec<T> base = result;
  for (T x : base) {
    if (x != numeric_limits<T>::lowest()) result.push_back(x - 1);
    if (x != numeric_limits<T>::max()) result.push_back(x + 1);
  }
  sort(all(result));
  result.erase(unique(all(result)), result.end());
  return result;
}

template <class T>
void check_range(const WaveletMatrix<T>& wm, const vec<T>& a,
                 const vec<T>& probes, int l, int r) {
  ++checked_ranges;
  const int n = int(a.size());
  const auto span = wm(l, r);
  require(span.size() == r - l, "span size", n, l, r);
  vec<T> sorted(a.begin() + l, a.begin() + r);
  sort(all(sorted));
  for (int k = 0; k < r - l; ++k)
    require(span.kth_smallest(k) == sorted[k], "kth_smallest", n, l, r);

  for (T x : probes) {
    const auto lo = lower_bound(all(sorted), x);
    const auto hi = upper_bound(all(sorted), x);
    require(span.count(x) == hi - lo, "count", n, l, r);
    require(span.range_freq(x) == lo - sorted.begin(), "range_freq(<)", n, l,
            r);
    const bool has_prev = lo != sorted.begin();
    const bool has_next = lo != sorted.end();
    // prev_value/next_value are undefined when no such value exists, so only
    // call them when the precondition (checkable via range_freq) holds.
    require(has_prev ? span.prev_value(x) == *std::prev(lo)
                     : span.range_freq(x) == 0,
            "prev_value", n, l, r);
    require(has_next ? span.next_value(x) == *lo
                     : span.range_freq(x) == int(sorted.size()),
            "next_value", n, l, r);
    for (T upper : probes) {
      const int expected =
          upper <= x ? 0 : int(lower_bound(all(sorted), upper) - lo);
      require(span.range_freq(x, upper) == expected,
              "range_freq([lower,upper))", n, l, r);
    }
    require(span.size() == r - l && span.count(x) == hi - lo &&
                span.range_freq(x) == lo - sorted.begin() &&
                (!has_prev || span.prev_value(x) == *std::prev(lo)) &&
                (!has_next || span.next_value(x) == *lo),
            "span stable after interleaved queries", n, l, r);
    if (!sorted.empty())
      require(span.kth_smallest(0) == sorted.front() &&
                  span.kth_smallest(span.size() - 1) == sorted.back(),
              "span extrema after interleaved queries", n, l, r);
  }
  for (int k = 0; k < r - l; ++k)
    require(span.kth_smallest(k) == sorted[k], "span kth results unchanged", n,
            l, r);
}

template <class T>
void check_array(const vec<T>& a, bool exhaustive, mt19937_64& rng) {
  const WaveletMatrix<T> wm(a);
  const int n = int(a.size());
  for (int i = 0; i < n; ++i)
    require(wm.access(i) == a[i], "access", n, i, i + 1);
  const vec<T> probes = thresholds(a);
  if (exhaustive) {
    for (int l = 0; l <= n; ++l)
      for (int r = l; r <= n; ++r) check_range(wm, a, probes, l, r);
  } else {
    vec<int> ends = {0, 1, 2, 62, 63, 64, 65, 66, 126, 127, 128, 129, n};
    ends.erase(remove_if(all(ends), [n](int x) { return x > n; }), ends.end());
    sort(all(ends));
    ends.erase(unique(all(ends)), ends.end());
    for (int l : ends)
      for (int r : ends)
        if (l <= r) check_range(wm, a, probes, l, r);
    for (int i = 0; i <= n; ++i) check_range(wm, a, probes, i, i);
    for (int trial = 0; trial < 80; ++trial) {
      int l = int(rng() % (n + 1)), r = int(rng() % (n + 1));
      if (l > r) swap(l, r);
      check_range(wm, a, probes, l, r);
    }
  }
}

// Return only a view; the caller retains the owner for its entire lifetime.
template <class T>
typename WaveletMatrix<T>::Span stored_view(const WaveletMatrix<T>& owner, ll l,
                                            ll r) {
  return owner(l, r);
}

template <class T>
void check_stored_views() {
  const WaveletMatrix<T> owner(vec<T>{9, -2, 5, 5, 1, 8});
  const auto left = owner(1, 4);
  const auto copied = left;
  const auto right = owner(4, 6);
  const auto returned = stored_view(owner, 0, 2);
  auto assigned = left;
  assigned = right;
  require(assigned.size() == 2 && assigned.kth_smallest(0) == T(1),
          "view assignment to another range", 6, 4, 6);
  const WaveletMatrix<T> other(vec<T>{42});
  assigned = other(0, 1);
  require(assigned.size() == 1 && assigned.kth_smallest(0) == T(42) &&
              assigned.count(T(42)) == 1,
          "view assignment to another owner", 1, 0, 1);
  auto check_left = [](const typename WaveletMatrix<T>::Span& view) {
    require(view.size() == 3 && view.kth_smallest(0) == -2 &&
                view.kth_smallest(1) == 5 && view.kth_smallest(2) == 5 &&
                view.count(5) == 2 && view.range_freq(5) == 1 &&
                view.range_freq(-2, 6) == 3 && view.prev_value(5) == T(-2) &&
                view.next_value(0) == T(5),
            "stored/copied view", 6, 1, 4);
  };
  for (int repeat = 0; repeat < 3; ++repeat) {
    check_left(left);
    require(right.size() == 2 && right.kth_smallest(0) == 1 &&
                right.kth_smallest(1) == 8 && right.count(5) == 0 &&
                right.range_freq(5) == 1 && right.range_freq(1, 8) == 1 &&
                right.range_freq(9) == 2 && right.prev_value(8) == T(1) &&
                right.next_value(8) == T(8),
            "simultaneous different view", 6, 4, 6);
    check_left(copied);
    require(returned.size() == 2 && returned.kth_smallest(0) == -2 &&
                returned.kth_smallest(1) == 9 && returned.count(9) == 1 &&
                returned.range_freq(9) == 1 && returned.range_freq(-2) == 0 &&
                returned.range_freq(-2, 10) == 2 &&
                returned.prev_value(0) == T(-2) &&
                returned.next_value(0) == T(9),
            "helper-returned view with live owner", 6, 0, 2);
    check_left(left);
  }
}

template <class T>
void run_type(mt19937_64& rng) {
  check_stored_views<T>();
  const T low = numeric_limits<T>::lowest(), high = numeric_limits<T>::max();
  for (const vec<T>& a : {vec<T>{}, vec<T>{0}, vec<T>{low}, vec<T>{high},
                          vec<T>{low, high, low, 0, high, -1, 1},
                          vec<T>{high, high, high}, vec<T>{low, low, low}})
    check_array(a, true, rng);

  // Exhaust all arrays over {-1, 0, 1} up to length five, and every valid
  // range.
  int combinations = 1;
  for (int n = 0; n <= 5; ++n) {
    for (int mask = 0; mask < combinations; ++mask) {
      vec<T> a(n);
      int digits = mask;
      for (auto& x : a) {
        x = T(digits % 3 - 1);
        digits /= 3;
      }
      check_array(a, true, rng);
    }
    combinations *= 3;
  }

  const vec<T> pool = {low,  T(low + 1), T(-100), T(-2),       T(-1), T(0),
                       T(1), T(2),       T(100),  T(high - 1), high};
  for (int trial = 0; trial < 60; ++trial) {
    vec<T> a(rng() % 13);
    for (auto& x : a) x = pool[rng() % pool.size()];
    check_array(a, true, rng);
  }

  for (int n : {63, 64, 65, 127, 128, 129}) {
    for (T value : {low, T(0), high}) check_array(vec<T>(n, value), false, rng);
    vec<T> alternating(n), increasing(n), random(n);
    for (int i = 0; i < n; ++i) {
      alternating[i] = i % 2 ? high : low;
      increasing[i] = T(i - n / 2);
      random[i] = pool[rng() % pool.size()];
    }
    check_array(alternating, false, rng);
    check_array(increasing, false, rng);
    reverse(all(increasing));
    check_array(increasing, false, rng);
    check_array(random, false, rng);
  }
}
}  // namespace

int main() {
  mt19937_64 rng(0x574156454c4554ULL);
  run_type<int>(rng);
  run_type<ll>(rng);
  const WaveletMatrix<> default_type(vl{LLONG_MIN, 0, LLONG_MAX});
  require(default_type(0, 3).kth_smallest(2) == LLONG_MAX,
          "default template argument", 3, 0, 3);
  cout << "WaveletMatrix regression passed (" << checked_ranges << " ranges)\n";
}
