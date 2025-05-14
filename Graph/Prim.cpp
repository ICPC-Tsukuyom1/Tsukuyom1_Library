struct MST {
    ll cost;
    Edges edges;
};
MST Prim(Graph &G) {
    ll total = 0ll;
    vector<ll>used(G.size());
    vector<Edge*>dist(G.size());
    using pi = pair<ll, ll>;
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.emplace(0ll,0);
    Edges edges;
    while (!Q.empty()) {
        auto p = Q.top(); Q.pop();
        if (used[p.second])continue;
        used[p.second] = true;
        total += p.first;
        if (dist[p.second]) edges.emplace_back(*dist[p.second]);
        for (auto e : G[p.second]) {
            if (used[e.to] || (dist[e.to] && dist[e.to]->cost <= e.cost)) continue;
            Q.emplace(e.cost, e.to);
        }
    }
    return {total, edges};
}
