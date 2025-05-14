void dfs(Graph &G, vector<ll>&dist, int v) {
    for (Edge e : G[v]) {
        if (dist[e.to] != INF) {
            continue;
        }
        dist[e.to] = dist[v] + e.cost;
        dfs(G, dist, e.to);
    }
}
