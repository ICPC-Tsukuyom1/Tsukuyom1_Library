/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/manhattanMST.cpp */
// depends on: Point, UnionFind
// マンハッタン距離による最小全域木。座標は整数であることを仮定する。
// 返り値は {重み, u, v} の配列（頂点数 n に対し n-1 本、n = 1 なら空）。
vec<array<ll, 3>> manhattanMST(Polygon ps) {
  ll n = sz(ps);
  vec<pair<ll, ll>> edges;
  vl id(n);
  iota(all(id), 0);
  rep(ph, 4) {
    stable_sort(all(id), [&](ll i, ll j) {
      ll ixy = (ll)(ps[i].x + ps[i].y), jxy = (ll)(ps[j].x + ps[j].y);
      ll iy = (ll)ps[i].y, jy = (ll)ps[j].y;
      return tie(ixy, iy) > tie(jxy, jy);
    });
    vl xv(n);
    rep(i, n) xv[i] = (ll)ps[i].x;
    sort(all(xv));
    xv.erase(unique(all(xv)), xv.end());
    ll m = sz(xv);
    vec<pair<ll, ll>> fen(m, pair<ll, ll>{LLONG_MIN, -1});
    for (ll idx : id) {
      ll xi = lower_bound(all(xv), (ll)ps[idx].x) - xv.begin();
      pair<ll, ll> ma{LLONG_MIN, -1};
      for (ll i = xi + 1; i > 0; i -= i & -i)
        if (ma.first <= fen[i - 1].first) ma = fen[i - 1];
      if (ma.second != -1) edges.push_back({idx, ma.second});
      ll v = (ll)(ps[idx].x - ps[idx].y);
      for (ll i = xi + 1; i <= m; i += i & -i)
        if (fen[i - 1].first <= v) fen[i - 1] = {v, idx};
    }
    rep(i, n) {
      swap(ps[i].x, ps[i].y);
      if (ph == 1) ps[i].y *= -1;
    }
  }
  auto dist = [&](ll i, ll j) {
    return llabs((ll)ps[i].x - (ll)ps[j].x) +
           llabs((ll)ps[i].y - (ll)ps[j].y);
  };
  stable_sort(all(edges), [&](pair<ll, ll> x, pair<ll, ll> y) {
    return dist(x.first, x.second) < dist(y.first, y.second);
  });
  UnionFind uf(n);
  vec<array<ll, 3>> res;
  for (auto [u, v] : edges) {
    if (uf.root(u) == uf.root(v)) continue;
    uf.unite(u, v);
    res.push_back({dist(u, v), u, v});
  }
  return res;
}
