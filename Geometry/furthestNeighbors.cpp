/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/furthestNeighbors.cpp */
// depends on: Point
// Q は反時計回りの狭義凸多角形。
// 各頂点 i について、最も距離が大きい頂点の番号 f[i] を返す。
// 距離行列が totally monotone であることを使った分割統治で O(n log n)。
vec<ll> furthestNeighbors(const Polygon &Q) {
  ll n = sz(Q);
  auto value = [&](ll i, ll j) -> ld {
    if (j <= i) return (ld)(j - i);
    if (j >= i + n) return (ld)-1;
    return (Q[i] - Q[j % n]).norm();
  };
  vec<ll> res(n);
  auto dfs = [&](auto &&self, ll rl, ll rr, ll cl, ll cr) -> void {
    if (rl == rr) return;
    ll r = (rl + rr) / 2;
    ll best = cl;
    for (ll c = cl + 1; c < cr; c++)
      if (value(r, best) < value(r, c)) best = c;
    res[r] = best % n;
    self(self, rl, r, cl, best + 1);
    self(self, r + 1, rr, best, cr);
  };
  dfs(dfs, 0, n, 0, 2 * n - 1);
  return res;
}
