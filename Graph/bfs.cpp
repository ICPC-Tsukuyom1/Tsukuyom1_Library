void bfs(Graph& G, ll s, vector<ll>& dist) {
    queue<ll>Q;
    dist[s] = 0; Q.push(s);
    while (!Q.empty()) {
        ll v = Q.front(); Q.pop();
        for (auto nv : G[v]) {
            if (dist[nv.to] == INF) {
                dist[nv.to] = dist[v] + 1;
                Q.push(nv.to);
            }
        }
    }
}
