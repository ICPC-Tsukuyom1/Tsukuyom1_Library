struct Edge {
  ll from, to, cost;
};
bool bellman_ford(vec<Edge> &edges, vl &dist, ll V, ll s) {
  dist = vl(V, INF);
  dist[s] = 0;
  rep(i, V - 1) {
    for (auto e : edges) {
      if (dist[e.from] == INF) continue;
      chmin(dist[e.to], dist[e.from] + e.cost);
    }
  }
  for (auto e : edges) {
    if (dist[e.from] == INF) continue;
    chmin(dist[e.to], dist[e.from] + e.cost);
  }
}
for (auto e : edges) {
  if (dist[e.from] == INF) continue;
  if (dist[e.to] > dist[e.from] + e.cost) { return false; }
}
return true;
}