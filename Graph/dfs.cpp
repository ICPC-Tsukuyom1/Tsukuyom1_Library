<<<<<<< HEAD
void dfs(vv<pll> &G, vl &dist, int v) {
    for (pll e : G[v]) {
        if (dist[e.first] != INF) {
            continue;
        }
        dist[e.first] = dist[v] + e.second;
        dfs(G, dist, e.first);
    }
=======
// need: Graph.cpp
void dfs(Graph &G, vector<ll> &dist, int v) {
  for (Edge e : G[v]) {
    if (dist[e.to] != INF) { continue; }
    dist[e.to] = dist[v] + e.cost;
    dfs(G, dist, e.to);
  }
>>>>>>> main
}
