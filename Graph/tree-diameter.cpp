/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Graph/tree-diameter.cpp */
// 木の直径(辺の重みは非負) — 2 回の DFS で O(V)。
// DFS は明示スタックの反復実装で、深い木でもスタックオーバーフローしない(§4 / #78)。
struct TreeDiameter {
  ll n;
  vv<pair<ll, ll>> g;  // g[v] = {to, w} の隣接リスト

  explicit TreeDiameter(ll n) : n(n), g(n) {}

  void add_edge(ll u, ll v, ll w) {
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  // 頂点 s からの最遠点を (距離, 頂点) で返す
  pair<ll, ll> farthest(ll s) const {
    vec<ll> dist(n, -1);
    vec<ll> st{s};
    dist[s] = 0;
    ll far = s;
    while (sz(st)) {
      ll v = st.back();
      st.pop_back();
      if (dist[v] > dist[far]) far = v;
      for (auto &[to, w] : g[v]) {
        if (dist[to] < 0) {
          dist[to] = dist[v] + w;
          st.push_back(to);
        }
      }
    }
    return {dist[far], far};
  }

  // 直径を返す
  ll diameter() const {
    ll u = farthest(0).second;
    return farthest(u).first;
  }
};
