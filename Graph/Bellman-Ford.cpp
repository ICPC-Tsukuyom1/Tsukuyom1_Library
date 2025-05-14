vector<ll> bellman_ford(Edges &edges, ll V, ll s) {
    vector<ll> dist(V, INF);
    dist[s] = 0;
    for (ll i = 0; i < V - 1; i++) {
        for (auto e : edges) {
            if (dist[e.from] == INF) continue;
            dist[e.to] = min(dist[e.to], dist[e.from] + e.cost);
        }
    }
    for (auto e : edges) {
        if (dist[e.from] == INF) continue;
        if (dist[e.from] + e.cost < dist[e.to]) return vector<ll>();
    }
    return dist;
}
