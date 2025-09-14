void bfs(vv<pll>& G, ll s, vector<ll>& dist) {
    queue<ll>Q;
    dist[s] = 0; Q.push(s);
    while (!Q.empty()) {
        ll v = Q.front(); Q.pop();
        for (auto nv : G[v]) {
            if (dist[nv.first] == INF) {
                dist[nv.first] = dist[v] + nv.second;
                Q.push(nv.first);
            }
        }
    }
}
