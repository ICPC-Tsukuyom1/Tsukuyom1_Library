bool bellman_ford(Edges &edges, vector<ll> &dist, ll V, ll s) {
    dist = vector<ll>(V, INF);
    dist[s] = 0;
    rep(i, V - 1) {
        for (auto e : edges) {
            if (dist[e.from] == INF) continue;
            chmin(dist[e.to], dist[e.from] + e.cost);
        }
    }
    for (auto e : edges) {
    	if (dist[e.from] == INF) continue;
    	if (dist[e.to] > dist[e.from] + e.cost) {
    		return false;
    	}
    }
    return true;
}