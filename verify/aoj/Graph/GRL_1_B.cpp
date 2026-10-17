//@aoj GRL_1_B

#include "../../../template.cpp"
#include "../../../Graph/Bellman-Ford.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll V, E, r;
  cin >> V >> E >> r;
  vec<Edge> edges(E);
  rep(i, E) cin >> edges[i].from >> edges[i].to >> edges[i].cost;
  vl dist;
  if (!bellman_ford(edges, dist, V, r)) {
    cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  const ll INF = 1e18;
  rep(i, V) {
    if (dist[i] == INF)
      cout << "INF\n";
    else
      cout << dist[i] << '\n';
  }
}
