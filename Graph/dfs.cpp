void dfs(vv<pll> &G, vl &dist, int v) {
    for (pll e : G[v]) {
        if (dist[e.first] != INF) {
            continue;
        }
        dist[e.first] = dist[v] + e.second;
        dfs(G, dist, e.first);
    }
}
