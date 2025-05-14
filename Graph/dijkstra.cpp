void dijkstra(const Graph &G, ll s, vector<long long>& dis) {
    int N = G.size();
    dis.assign(N, INF);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while (!pq.empty()) {
        pair<ll, ll> p = pq.top(); pq.pop();
        int v = p.second;
        if (dis[v] < p.first) {
            continue;
        }
        for (auto& e : G.G[v]) {
            if (dis[e.to] > dis[v] + e.cost) {
                dis[e.to] = dis[v] + e.cost;
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}
