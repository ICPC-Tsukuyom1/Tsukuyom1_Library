/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Structure/BIT2d-sparse.cpp */
template <class T>
struct BIT2dSparse {
 private:
  ll n;
  vl xs;
  vv<ll> ys;
  vv<T> bit;
  ll ix(ll x) const { return lower_bound(all(xs), x) - xs.begin(); }
  ll iy(ll i, ll y) const { return lower_bound(all(ys[i]), y) - ys[i].begin(); }

 public:
  // O(n log^2 n)
  BIT2dSparse(const vec<pll>& points) {
    for (auto& p : points) xs.push_back(p[0]);
    sort(all(xs)), xs.erase(unique(all(xs)), xs.end());
    n = sz(xs), ys.resize(n + 1), bit.resize(n + 1);
    for (auto& p : points)
      for (ll i = ix(p[0]) + 1; i <= n; i += i & -i) ys[i].push_back(p[1]);
    for (ll i = 1; i <= n; i++) {
      sort(all(ys[i]));
      ys[i].erase(unique(all(ys[i])), ys[i].end());
      bit[i].assign(sz(ys[i]) + 1, T(0));
    }
  }

  // [x][y] += c. O(log^2 n)
  void add(ll x, ll y, T c) {
    for (ll i = ix(x) + 1; i <= n; i += i & -i)
      for (ll j = iy(i, y) + 1; j < sz(bit[i]); j += j & -j) bit[i][j] += c;
  }

  // sum [-inf, x), [-inf, y). O(log^2 n)
  T sum(ll x, ll y) const {
    T ret = 0;
    for (ll i = ix(x); i > 0; i -= i & -i)
      for (ll j = iy(i, y); j > 0; j -= j & -j) ret += bit[i][j];
    return ret;
  }

  // sum [x1, x2), [y1, y2). O(log^2 n)
  T sum(ll x1, ll x2, ll y1, ll y2) const {
    return sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1);
  }
};
