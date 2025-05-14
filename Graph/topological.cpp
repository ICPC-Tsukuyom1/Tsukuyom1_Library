vector<ll> topological_sort(Graph &G) {
    vector<ll> ans;
    ll N = (ll)G.size();
    vector<ll> ind(N);
    for (ll i = 0; i < N; i++) {
        for (auto e : G[i]) {
            ind[e.to]++;
        }
    }
    queue<ll> Q;
    for (ll i = 0; i < N; i++) {
        if (ind[i] == 0) Q.push(i);
    }
    while (!Q.empty()) {
        ll v = Q.front();
        ans.push_back(v);
        Q.pop();
        for (auto e : G[v]) {
            ind[e.to]--;
            if (ind[e.to] == 0) Q.push(e.to);
        }
    }
    return ans;
}
