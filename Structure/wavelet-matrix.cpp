template <class T = ll>
struct WaveletMatrix {
 private:
  struct BitVector {
    vec<uint64_t> bits;
    vec<int> sum;
    ll mid;
    // The extra word lets rank(n) read bits[n / 64] even when n % 64 == 0.
    BitVector(const auto& a, ll d) : bits(sz(a) / 64 + 1), sum(sz(bits) + 1) {
      rep(i, sz(a)) if ((a[i] >> d) & 1) bits[i / 64] |= 1ULL << (i % 64);
      rep(i, sz(bits)) sum[i + 1] = sum[i] + popcount(bits[i]);
      mid = sz(a) - sum.back();
    }
    ll rank(ll r) const {
      return sum[r / 64] + popcount(bits[r / 64] & ((1ULL << (r % 64)) - 1));
    }
  };

  ll n, lg;
  vec<T> values;
  vec<BitVector> bv;

  ll index(const T& x) const {
    return lower_bound(all(values), x) - values.begin();
  }

 public:
  WaveletMatrix(const vec<T>& a) : n(sz(a)), values(a) {
    sort(all(values));
    values.erase(unique(all(values)), values.end());
    values.shrink_to_fit();
    lg = bit_width(values.size() - !values.empty());
    vec<int> cur(n);
    rep(i, n) cur[i] = index(a[i]);
    rrep(d, 0, lg) {
      bv.emplace_back(cur, d);
      stable_partition(all(cur), [d](int x) { return !((x >> d) & 1); });
    }
  }

  struct Span {
   private:
    friend class WaveletMatrix;
    Span(const WaveletMatrix* w, ll l, ll r) : w(w), l(l), r(r) {}
    const WaveletMatrix* w;
    ll l, r;

    // kth: {value ID, count}; otherwise: {less, equal}.
    template <bool kth = false>
    pll query(ll x) const {
      auto [w, l, r] = *this;
      if (!kth && x == sz(w->values)) return {r - l, 0};
      ll ans = 0, bit = 1LL << w->lg;
      for (auto& b : w->bv) {
        bit >>= 1;
        ll a = b.rank(l), c = b.rank(r);
        l -= a;
        r -= c;
        if (kth ? x >= r - l : x & bit) {
          ans += kth ? bit : r - l;
          x -= kth ? r - l : 0;
          l = b.mid + a;
          r = b.mid + c;
        }
      }
      return {ans, r - l};
    }

   public:
    ll size() const { return r - l; }
    T kth_smallest(ll k) const { return w->values[query<true>(k)[0]]; }

    ll count(const T& x) const {
      ll id = w->index(x);
      return id < sz(w->values) && w->values[id] == x ? query(id)[1] : 0;
    }

    ll range_freq(const T& upper) const { return query(w->index(upper))[0]; }

    ll range_freq(const T& lower, const T& upper) const {
      return lower < upper ? range_freq(upper) - range_freq(lower) : 0;
    }

    // Precondition: range_freq(upper) > 0; otherwise undefined behavior.
    T prev_value(const T& upper) const {
      return kth_smallest(range_freq(upper) - 1);
    }

    // Precondition: range_freq(lower) < size(); otherwise undefined behavior.
    T next_value(const T& lower) const {
      return kth_smallest(range_freq(lower));
    }
  };

  Span operator()(ll l, ll r) const { return {this, l, r}; }
  T access(ll i) const { return (*this)(i, i + 1).kth_smallest(0); }
};
