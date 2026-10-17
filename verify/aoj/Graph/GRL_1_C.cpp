//@aoj GRL_1_C

#include "../../../template.cpp"
#include "../../../Graph/Bellman-Ford.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll V, E;
  cin >> V >> E;
  vec<Edge> edges(E);
  rep(i, E) cin >> edges[i].from >> edges[i].to >> edges[i].cost;
  // ライブラリに Floyd-Warshall が無いので全始点 Bellman-Ford (V<=100 なので間に合う)。
  // 負閉路はその閉路上の頂点を始点にすれば必ず検出できる。
  const ll INF = 1e18;
  vv<ll> dist(V);
  rep(r, V) {
    if (!bellman_ford(edges, dist[r], V, r)) {
      cout << "NEGATIVE CYCLE\n";
      return 0;
    }
  }
  rep(i, V) {
    rep(j, V) {
      if (j) cout << ' ';
      if (dist[i][j] == INF)
        cout << "INF";
      else
        cout << dist[i][j];
    }
    cout << '\n';
  }
}
