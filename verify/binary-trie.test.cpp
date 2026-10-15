#include "../template.cpp"

struct T {
  ll count, sum, minimum, divisor;
  bool operator==(const T&) const = default;
};

const T e{0, 0, LLONG_MAX, 0};
T monoid_identity() { return e; }
T op(const T& a, const T& b) {
  return {a.count + b.count, a.sum + b.sum, min(a.minimum, b.minimum),
          gcd(a.divisor, b.divisor)};
}
#include "../Structure/binary-trie.cpp"

using U = unsigned long long;
template <ll B = 63>
using Trie = BinaryTrie<T, &op, &monoid_identity, B>;

template <class N>
vector<N*> collect_nodes(N* root) {
  vector<N*> nodes;
  auto dfs = [&](auto&& self, N* node) -> void {
    if (!node) return;
    nodes.push_back(node);
    for (auto* child : node->ch) self(self, child);
  };
  dfs(dfs, root);
  return nodes;
}

template <int B, class Key = U>
struct Test {
  using U = Key;
  using DefaultTrie = BinaryTrie<T, &op, &monoid_identity>;
  using SizedTrie = BinaryTrie<T, &op, &monoid_identity, B>;
  static_assert(B != 63 || is_same_v<DefaultTrie, SizedTrie>);
  SizedTrie trie;
  map<U, T> oracle;
  map<U, ll> counts;
  mt19937_64 rng{0x6b8b4567327b23c6ULL ^ B};

  static constexpr U key_mask() {
    return numeric_limits<U>::max() >> (numeric_limits<U>::digits - B);
  }
  U random_key() { return rng() & key_mask(); }
  T payload() {
    if (rng() % 5 == 0) return e;
    return {(ll)(rng() % 3) + 1, (ll)(rng() % 2001) - 1000,
            (ll)(rng() % 1000) + 1, (ll)(rng() % 120) + 1};
  }
  void insert(U x, T value) {
    trie.insert(x, value);
    auto [it, fresh] = oracle.try_emplace(x, e);
    (void)fresh;
    it->second = op(it->second, value);
    ++counts[x];
  }
  void erase(U x) {
    auto nodes = collect_nodes(trie.root).size();
    trie.erase(x);
    oracle.erase(x);
    counts.erase(x);
    // Neither successful nor absent-key deletion may allocate or free nodes.
    assert(collect_nodes(trie.root).size() == nodes);
  }
  void xor_all(U mask) {
    trie.xor_all(mask);
    map<U, T> next;
    map<U, ll> next_counts;
    for (const auto& [x, value] : oracle) next.emplace(x ^ mask, value);
    for (const auto& [x, count] : counts) next_counts.emplace(x ^ mask, count);
    oracle.swap(next);
    counts.swap(next_counts);
  }
  T aggregate() const {
    T result = e;
    for (const auto& [x, value] : oracle) {
      (void)x;
      result = op(result, value);
    }
    return result;
  }
  void check_range(U l, U r, U mask = 0) {
    T expected = e;
    for (const auto& [x, value] : oracle) {
      U y = x ^ mask;
      if (l <= y && y < r) expected = op(expected, value);
    }
    trie.xor_all(mask);
    const auto& actual = trie;
    assert(actual.query(l, r) == expected);
    trie.xor_all(mask);
  }
  void check_structure() const {
    assert(trie.root);
    auto dfs = [&](auto&& self, const auto* node, int depth) -> void {
      if (!node) return;
      const auto& [children, value, count, lazy] = *node;
      (void)value;
      if (depth == B) {
        assert(lazy == 0);
        assert(!children[0] && !children[1]);
      } else {
        self(self, children[0], depth + 1);
        self(self, children[1], depth + 1);
        assert(count == (children[0] ? children[0]->cnt : 0) +
                            (children[1] ? children[1]->cnt : 0));
      }
    };
    dfs(dfs, trie.root, 0);
  }
  void check() {
    check_structure();
    const auto& actual = trie;
    T total = aggregate();
    ll total_count = 0;
    for (const auto& [x, count] : counts) total_count += count;
    assert(actual.size() == total_count);
    assert(actual.query_all() == total);
    for (const auto& [x, value] : oracle) {
      assert(actual.get(x) == value);
      assert(actual.count(x) == counts.at(x));
    }
    rep(i, 8) {
      U x = random_key();
      auto it = oracle.find(x);
      assert(actual.get(x) == (it == oracle.end() ? e : it->second));
      assert(actual.count(x) == (it == oracle.end() ? 0 : counts.at(x)));
    }
    for (U mask :
         vector<U>{0, 1, U(U(1) << (B - 1)), key_mask(), random_key()}) {
      vector<U> sorted;
      for (const auto& [x, count] : counts)
        rep(i, count) sorted.push_back(x ^ mask);
      sort(all(sorted));
      trie.xor_all(mask);
      rep(k, sz(sorted)) assert(actual.at(k) == sorted[k]);
      assert(actual.query_all() == total);
      trie.xor_all(mask);
      check_range(0, 0, mask);
      check_range(key_mask(), key_mask(), mask);
      check_range(key_mask(), 0, mask);
      check_range(1, 0, mask);
      if constexpr (B < min<ll>(63, numeric_limits<U>::digits))
        check_range(0, U(U(1) << B), mask);
      else check_range(0, key_mask(), mask);
      for (const auto& [x, value] : oracle) {
        (void)value;
        U y = x ^ mask;
        check_range(0, y, mask);
        check_range(y, key_mask(), mask);
        if (y != key_mask()) check_range(y, U(y + 1), mask);
      }
      rep(i, 6) {
        U l = random_key(), r = random_key();
        check_range(l, r, mask);
        if (l > r) swap(l, r);
        check_range(l, r, mask);
      }
    }
  }
  void clear() {
    while (!oracle.empty()) erase(oracle.begin()->first);
  }
  void boundaries() {
    U high = U(U(1) << (B - 1));
    vector<U> keys{0, 1, U(high - 1), high, U(key_mask() - 1), key_mask()};
    sort(all(keys));
    keys.erase(unique(all(keys)), keys.end());
    check();
    for (U x : keys) erase(x);
    assert(collect_nodes(trie.root).size() == 1);
    xor_all(key_mask());
    for (U x : keys) {
      insert(x, e);
      check();
      insert(x, {2, 17, 31, 12});
      insert(x, {3, -19, 7, 18});
      assert((trie.get(x) == T{5, -2, 7, 6}));
      check();
    }
    xor_all(high);
    xor_all(key_mask());
    check();
    clear();
    check();
    xor_all(high);
    for (U x : keys) {
      insert(x, {3, 29, 13, 42});
      auto nodes = collect_nodes(trie.root).size();
      erase(x);
      assert(trie.get(x) == e);
      assert(collect_nodes(trie.root).size() == nodes);
      insert(x, {2, -19, 5, 24});
      assert(collect_nodes(trie.root).size() == nodes);
      check();
    }
    clear();
  }
  void random_update() {
    U x = random_key();
    if (!oracle.empty() && rng() % 4 != 0) {
      auto it = oracle.begin();
      advance(it, rng() % oracle.size());
      x = it->first;
    }
    switch (rng() % 6) {
      case 0:
      case 1:
      case 2:
        if (oracle.size() >= 20 && !oracle.count(x)) x = oracle.begin()->first;
        insert(x, payload());
        break;
      case 3:
        xor_all(random_key());
        break;
      default:
        erase(x);
        break;
    }
  }
  void lazy_batches() {
    const U high = U(U(1) << (B - 1)), maximum = key_mask();
    insert(0, {2, 11, 7, 12});
    insert(maximum, {3, -19, 13, 18});
    xor_all(high);
    xor_all(1);
    xor_all(maximum);
    U pending = high ^ 1 ^ maximum;
    assert(trie.root->lazy == pending);
    const auto& actual = trie;
    assert(actual.size() == 2);
    assert(actual.query_all() == aggregate());
    assert(trie.root->lazy == pending);
    if constexpr (B < min<ll>(63, numeric_limits<U>::digits)) {
      assert(actual.query(0, U(U(1) << B)) == aggregate());
      assert(trie.root->lazy == pending);
    }
    insert(pending, {4, 31, 5, 30});
    erase(maximum ^ pending);
    xor_all(high);
    insert(maximum, e);
    erase(1);
    check();

    // Partial apply/query/undo leaves tags at different depths before updates.
    check_range(0, high, maximum);
    insert(0, {2, 43, 3, 42});
    xor_all(maximum);
    erase(maximum);
    insert(high, {1, 53, 19, 66});
    check();
    clear();
    xor_all(high);
    xor_all(maximum);
    insert(0, {2, 83, 31, 102});
    insert(maximum, {3, -97, 37, 114});
    check();
    clear();
    // No get/size/at/query calls between these updates.
    rep(batch, 60) {
      rep(step, 24) random_update();
      check();
    }
    clear();
    check();
  }
  void run() {
    boundaries();
    rep(step, 180) {
      random_update();
      check();
    }
    clear();
    lazy_batches();
  }
};

void duplicate_updates() {
  Trie<> trie;
  static_assert(is_same_v<decltype(trie.get(0)), T>);
  trie.insert(5, {1, 11, 7, 12});
  trie.insert(5, {1, -19, 3, 18});
  assert(trie.size() == 2 && trie.count(5) == 2);
  assert((trie.get(5) == T{2, -8, 3, 6}));
  assert(trie.at(0) == 5 && trie.at(1) == 5);
  trie.xor_all(9);
  assert(trie.at(0) == 12 && trie.at(1) == 12);
  assert((trie.query(12, 13) == T{2, -8, 3, 6}));
  trie.erase(12);
  assert(trie.size() == 0 && trie.query_all() == e && trie.get(12) == e &&
         trie.count(12) == 0);
  trie.insert(12, {1, 17, 5, 24});
  assert(trie.size() == 1);
}

void nullptr_children() {
  Trie<> trie;
  const U high = 1ULL << 62, maximum = LLONG_MAX;
  assert(!trie.root->ch[0] && !trie.root->ch[1]);
  trie.xor_all(maximum);
  trie.erase(0);
  assert(collect_nodes(trie.root).size() == 1);
  trie.insert(high, {3, 7, 11, 6});
  assert(collect_nodes(trie.root).size() == 64);
  assert(!trie.root->ch[0] && trie.root->ch[1]);
  assert(trie.get(0) == e);
  assert(trie.size() == 1 && trie.at(0) == high);
  assert(trie.query(0, high) == e);
  assert((trie.query(high, high + 1) == T{3, 7, 11, 6}));
  trie.xor_all(high);
  assert(trie.at(0) == 0);
  assert(trie.root->ch[0] && !trie.root->ch[1]);
  trie.erase(high);
  trie.erase(0);
  assert(collect_nodes(trie.root).size() == 64);
  trie.xor_all(maximum);
  trie.insert(maximum, {1, 13, 17, 18});
  assert(collect_nodes(trie.root).size() == 64);
  assert(trie.at(0) == U(maximum));
  assert(trie.query(0, maximum) == e);
  assert((trie.query_all() == T{1, 13, 17, 18}));
}

void pointer_stability() {
  using Trie = ::Trie<30>;
  static_assert(!is_copy_constructible_v<Trie> && !is_copy_assignable_v<Trie>);
  static_assert(!is_move_constructible_v<Trie> && !is_move_assignable_v<Trie>);
  static_assert(!is_copy_constructible_v<::Trie<>>);
  static_assert(!is_move_constructible_v<::Trie<>>);
  Trie trie;
  trie.insert(0, {2, 11, 3, 9});
  auto* root = trie.root;
  auto saved = collect_nodes(root);
  rep(i, 8192) trie.insert((i + 1) * 65537ULL, {1, 1, 7, 6});
  auto nodes = collect_nodes(root);
  set<Trie::Node*> present(all(nodes));
  for (auto* node : saved) assert(present.count(node));
  assert(trie.root == root);
  assert((trie.get(0) == T{2, 11, 3, 9}));
  assert(trie.size() == 8193);
  assert((trie.query_all() == T{8194, 8203, 3, 3}));
  rep(i, 8192) {
    assert((trie.get((i + 1) * 65537ULL) == T{1, 1, 7, 6}));
    trie.erase((i + 1) * 65537ULL);
  }
  trie.erase(0);
  trie.xor_all(ULLONG_MAX >> 34);
  auto retained = collect_nodes(root);
  assert(set<Trie::Node*>(all(retained)) == present);
  assert(trie.root == root && trie.size() == 0);
}

namespace inline_lambda_test {
using Trie = BinaryTrie<pair<ll, ll>,
                        [](pair<ll, ll> a, pair<ll, ll> b) {
                          return pair<ll, ll>{a.first + b.first,
                                              min(a.second, b.second)};
                        },
                        []() { return pair<ll, ll>{0, LLONG_MAX}; }>;

void run() {
  Trie trie;
  trie.insert(0, {2, 3});
  trie.insert(0, {1, 2});
  const U high = 1ULL << 62, maximum = LLONG_MAX;
  trie.insert(high, {1, 4});
  trie.insert(maximum, {3, -5});
  const auto& actual = trie;
  assert(actual.size() == 4);
  assert((actual.get(0) == pair<ll, ll>{3, 2}));
  assert((actual.query_all() == pair<ll, ll>{7, -5}));
  assert((actual.query(0, maximum) == pair<ll, ll>{4, 2}));
  trie.xor_all(maximum);
  assert((actual.query(0, maximum) == pair<ll, ll>{4, -5}));
  assert(actual.at(0) == 0 && actual.at(1) == (maximum ^ high) &&
         actual.at(2) == maximum && actual.at(3) == maximum);
  trie.erase(0);
  assert((actual.get(0) == pair<ll, ll>{0, LLONG_MAX}));
  assert((actual.query_all() == pair<ll, ll>{4, 2}));
  assert(actual.size() == 3);
  trie.xor_all(maximum);
  trie.insert(0, {2, 1});
  assert((actual.get(0) == pair<ll, ll>{5, 1}));
}
}  // namespace inline_lambda_test

namespace no_count_test {
// Counts are maintained by the trie, independently of the aggregate type.
struct T {
  ll sum, minimum;
  bool operator==(const T&) const = default;
};
const T e{0, LLONG_MAX};
T identity() { return e; }
T op(const T& a, const T& b) {
  return {a.sum + b.sum, min(a.minimum, b.minimum)};
}
template <class Trie, int B>
void run_case() {
  Trie trie;
  const auto& actual = trie;
  trie.xor_all(15);
  trie.insert(2, e);
  assert(collect_nodes(trie.root).size() == B + 1);
  assert(actual.get(2) == e && actual.query_all() == e);
  assert(actual.size() == 1 && actual.at(0) == 2);
  trie.xor_all(8);
  trie.insert(10, {7, 5});
  assert(collect_nodes(trie.root).size() == B + 1);
  trie.insert(10, {-7, LLONG_MAX});
  assert((actual.get(10) == T{0, 5}));
  assert(actual.size() == 3 && actual.count(10) == 3 && actual.at(0) == 10 &&
         actual.at(1) == 10 && actual.at(2) == 10);
  // Zero sum cannot be treated as zero count or as an empty subtree.
  assert((actual.query(10, 11) == T{0, 5}));
  assert((actual.query_all() == T{0, 5}));
  trie.erase(10);
  assert(actual.query_all() == e);
  auto nodes = collect_nodes(trie.root).size();
  trie.insert(10, e);
  assert(collect_nodes(trie.root).size() == nodes);
  trie.xor_all(15);
  trie.insert(5, {11, 3});
  trie.insert(4, {-11, 7});
  assert((actual.query(4, 6) == T{0, 3}));
  trie.xor_all(8);
  assert((actual.query(12, 14) == T{0, 3}));
  trie.xor_all(8);
  trie.erase(5);
  assert((actual.query_all() == T{-11, 7}));
  trie.erase(4);
  assert(actual.get(4) == e && actual.query_all() == e);
}

void run() {
  run_case<BinaryTrie<T, &op, &identity>, 63>();
  run_case<BinaryTrie<T, &op, &identity, 4>, 4>();
}
}  // namespace no_count_test

namespace non_structural_test {
using Value = vector<ll>;
Value identity() { return {0, 0, 0}; }
// A non-structural T is returned by a factory, never passed as an NTTP value.
using Trie = BinaryTrie<Value,
                        [](Value a, const Value& b) {
                          rep(i, 3) a[i] += b[i];
                          return a;
                        },
                        &identity, 4>;
Value combine(Value a, const Value& b) {
  rep(i, 3) a[i] += b[i];
  return a;
}

void run() {
  Trie trie;
  map<uint8_t, Value> oracle;
  map<uint8_t, ll> counts;
  mt19937_64 rng{0x9e3779b97f4a7c15ULL};
  auto insert = [&](uint8_t x, Value value) {
    trie.insert(x, value);
    auto [it, fresh] = oracle.try_emplace(x, identity());
    (void)fresh;
    it->second = combine(it->second, value);
    ++counts[x];
  };
  auto check = [&]() {
    const auto& actual = trie;
    Value total = identity();
    vector<uint8_t> sorted;
    for (const auto& [x, value] : oracle) {
      total = combine(total, value);
      rep(i, counts[x]) sorted.push_back(x);
    }
    ll total_count = 0;
    for (const auto& [x, count] : counts) total_count += count;
    assert(actual.query_all() == total && actual.size() == total_count);
    rep(k, sz(sorted)) assert(actual.at(k) == sorted[k]);
    rep(x, 16) {
      auto it = counts.find(uint8_t(x));
      assert(actual.count(uint8_t(x)) == (it == counts.end() ? 0 : it->second));
    }
    rep(x, 16) {
      auto it = oracle.find(uint8_t(x));
      assert(actual.get(uint8_t(x)) ==
             (it == oracle.end() ? identity() : it->second));
    }
    // B=4 is narrower than uint8_t, so the exclusive endpoint 16 is valid.
    rep(l, 17) rep(r, 17) {
      Value expected = identity();
      for (const auto& [x, value] : oracle)
        if (l <= x && x < r) expected = combine(expected, value);
      assert(actual.query(uint8_t(l), uint8_t(r)) == expected);
    }
  };
  check();
  insert(0, {2, 7, -9});
  insert(0, {3, -7, 9});
  insert(8, {1, -5, 11});
  insert(15, {4, 13, -17});
  assert((trie.get(0) == Value{5, 0, 0}));
  check();
  rep(step, 400) {
    uint8_t x = uint8_t(rng() & 15);
    switch (rng() % 4) {
      case 0:
      case 1:
        insert(x, {(ll)(rng() % 3), (ll)(rng() % 101) - 50,
                   (ll)(rng() % 101) - 50});
        break;
      case 2:
        trie.erase(x);
        oracle.erase(x);
        counts.erase(x);
        break;
      default: {
        trie.xor_all(x);
        map<uint8_t, Value> next;
        map<uint8_t, ll> next_counts;
        for (const auto& [key, value] : oracle)
          next.emplace(uint8_t(key ^ x), value);
        for (const auto& [key, count] : counts)
          next_counts.emplace(uint8_t(key ^ x), count);
        oracle.swap(next);
        counts.swap(next_counts);
        break;
      }
    }
    check();
  }
  for (const auto& [x, value] : oracle) {
    (void)value;
    trie.erase(x);
  }
  oracle.clear();
  counts.clear();
  check();
}
}  // namespace non_structural_test

// Signed keys use only the nonnegative domain.
template <class Key, int B = numeric_limits<Key>::digits>
struct SignedTest {
  using Unsigned = make_unsigned_t<Key>;
  using DefaultTrie = BinaryTrie<T, &op, &monoid_identity>;
  using SizedTrie = BinaryTrie<T, &op, &monoid_identity, B>;
  static constexpr int width = numeric_limits<Unsigned>::digits;
  static_assert(is_signed_v<Key> && 1 <= B && B <= width);
  static_assert(B != 63 || is_same_v<DefaultTrie, SizedTrie>);
  static_assert(is_same_v<decltype(declval<const SizedTrie&>().at(0)), ll>);
  static_assert(
      is_same_v<decltype(declval<typename SizedTrie::Node>().lazy), ll>);
  static constexpr Key maximum() {
    constexpr Unsigned bits = numeric_limits<Unsigned>::max() >> (width - B);
    return Key(min(bits, Unsigned(numeric_limits<Key>::max())));
  }
  static constexpr Key high() {
    return Key(Unsigned(1) << (min(B, numeric_limits<Key>::digits) - 1));
  }

  SizedTrie trie;
  map<Key, T> oracle;
  map<Key, ll> counts;
  mt19937_64 rng{0x51a9ed1234ULL ^ B ^ width};

  Key random_key() { return Key(Unsigned(rng()) & Unsigned(maximum())); }
  T payload() {
    if (rng() % 5 == 0) return e;
    return {(ll)(rng() % 3) + 1, (ll)(rng() % 2001) - 1000,
            (ll)(rng() % 1000) + 1, (ll)(rng() % 120) + 1};
  }
  void insert(Key x, T value) {
    assert(x >= 0 && x <= maximum());
    trie.insert(x, value);
    auto [it, fresh] = oracle.try_emplace(x, e);
    (void)fresh;
    it->second = op(it->second, value);
    ++counts[x];
  }
  void erase(Key x) {
    auto nodes = collect_nodes(trie.root).size();
    trie.erase(x);
    oracle.erase(x);
    counts.erase(x);
    assert(collect_nodes(trie.root).size() == nodes);
  }
  void xor_all(Key mask) {
    assert(mask >= 0 && mask <= maximum());
    trie.xor_all(mask);
    map<Key, T> next;
    map<Key, ll> next_counts;
    for (const auto& [x, value] : oracle)
      next.emplace(Key(Unsigned(x) ^ Unsigned(mask)), value);
    for (const auto& [x, count] : counts)
      next_counts.emplace(Key(Unsigned(x) ^ Unsigned(mask)), count);
    oracle.swap(next);
    counts.swap(next_counts);
  }
  T aggregate() const {
    T result = e;
    for (const auto& [x, value] : oracle) {
      (void)x;
      result = op(result, value);
    }
    return result;
  }
  void check_range(Key l, Key r) const {
    T expected = e;
    for (const auto& [x, value] : oracle)
      if (l <= x && x < r) expected = op(expected, value);
    assert(trie.query(l, r) == expected);
  }
  void check() {
    const auto& actual = trie;
    const T total = aggregate();
    ll total_count = 0;
    for (const auto& [x, count] : counts) total_count += count;
    assert(actual.size() == total_count && actual.query_all() == total);
    vector<Key> sorted;
    for (const auto& [x, value] : oracle) {
      assert(actual.get(x) == value);
      assert(actual.count(x) == counts.at(x));
      rep(i, counts[x]) sorted.push_back(x);
    }
    rep(k, sz(sorted)) assert(actual.at(k) == sorted[k]);
    rep(i, 8) {
      Key x = random_key();
      auto it = oracle.find(x);
      assert(actual.get(x) == (it == oracle.end() ? e : it->second));
      check_range(random_key(), random_key());
      check_range(numeric_limits<Key>::lowest(), x);
    }
    check_range(0, 0);
    check_range(0, maximum());
    check_range(maximum(), maximum());
    check_range(maximum(), 0);
    check_range(numeric_limits<Key>::lowest(), maximum());
    check_range(-1, 1);
    check_range(numeric_limits<Key>::lowest(), -1);
    check_range(0, -1);
    check_range(-1, -1);
    check_range(numeric_limits<Key>::lowest(), 0);
    // A full positive endpoint exists only when the domain is below Key::max.
    if constexpr (maximum() < numeric_limits<Key>::max()) {
      Key end = Key(Unsigned(maximum()) + Unsigned(1));
      assert(actual.query(0, end) == total);
      assert(actual.query(numeric_limits<Key>::lowest(), end) == total);
    } else {
      T excluding_maximum = e;
      for (const auto& [x, value] : oracle)
        if (x != maximum()) excluding_maximum = op(excluding_maximum, value);
      assert(actual.query(0, maximum()) == excluding_maximum);
    }
  }
  void random_update() {
    Key x = random_key();
    if (!oracle.empty() && rng() % 4 != 0) {
      auto it = oracle.begin();
      advance(it, rng() % oracle.size());
      x = it->first;
    }
    switch (rng() % 6) {
      case 0:
      case 1:
      case 2:
        if (oracle.size() >= 20 && !oracle.count(x)) x = oracle.begin()->first;
        insert(x, payload());
        break;
      case 3:
        xor_all(random_key());
        break;
      default:
        erase(x);
    }
  }
  void run() {
    check();
    insert(0, e);
    // Also verify that the default signed width includes the unused sign bit.
    assert(collect_nodes(trie.root).size() == B + 1);
    vector<Key> keys{0,        1, Key(high() - 1), high(), Key(maximum() - 1),
                     maximum()};
    sort(all(keys));
    keys.erase(unique(all(keys)), keys.end());
    for (Key x : keys) {
      insert(x, {2, 17, 31, 12});
      insert(x, {3, -19, 7, 18});
      assert((trie.get(x) == T{5, -2, 7, 6}));
    }
    check();
    for (Key mask : vector<Key>{0, 1, high(), maximum()}) {
      xor_all(mask);
      check();
      xor_all(mask);
      check();
      // get/at/query have pushed tags before undo; update through those tags.
      erase(maximum());
      insert(maximum(), {2, 11, 3, 9});
      insert(0, {1, 7, 5, 6});
      check();
    }
    rep(batch, 60) {
      xor_all(maximum());
      auto pending = trie.root->lazy;
      assert(trie.query_all() == aggregate());
      ll count = 0;
      for (const auto& [x, n] : counts) count += n;
      assert(trie.size() == count);
      assert(trie.root->lazy == pending);
      // No queries between these insert/erase operations under pending tags.
      insert(0, {2, 13, 7, 12});
      erase(maximum());
      insert(maximum(), {3, -11, 5, 18});
      rep(step, 24) random_update();
      check();
    }
    while (!oracle.empty()) erase(oracle.begin()->first);
    xor_all(maximum());
    insert(0, {2, 11, 3, 9});
    erase(0);
    check();
  }
};

int main() {
  duplicate_updates();
  nullptr_children();
  inline_lambda_test::run();
  no_count_test::run();
  non_structural_test::run();
  pointer_stability();
  Test<1>().run();
  Test<4>().run();
  Test<30>().run();
  Test<63>().run();
  Test<62>().run();
  Test<numeric_limits<uint8_t>::digits, uint8_t>().run();
  Test<numeric_limits<uint16_t>::digits, uint16_t>().run();
  Test<numeric_limits<uint32_t>::digits, uint32_t>().run();
  Test<30, uint32_t>().run();
  Test<4, uint8_t>().run();
  SignedTest<int8_t>().run();
  SignedTest<int16_t>().run();
  SignedTest<int>().run();
  SignedTest<ll>().run();
  SignedTest<int8_t, 4>().run();
  SignedTest<int16_t, 4>().run();
  SignedTest<int, 4>().run();
  SignedTest<ll, 4>().run();
  SignedTest<int, 30>().run();
  SignedTest<ll, 30>().run();
  SignedTest<ll, 63>().run();
  cout << "BinaryTrie tests passed\n";
}
