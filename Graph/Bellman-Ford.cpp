bool bellman_ford(Edges &edges, vector<ll> &dist ll V, ll s) {
    dist = vector<ll>(V, INF);
    dist[s] = 0;
    for (ll i = 0; i < V; i++) {
        if(i == V-1) return false;
        bool load = false;
        for (auto e : edges) {
            if (dist[e.from] == INF) continue;
            if(chmin(dist[e.to], dist[e.from] + e.cost)){
                 load = true;
            }
        }
        if(!load) break;
    }
    return true;
}
