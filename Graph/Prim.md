# ✅プリム法

## なにこれ
最小全域木を構築する。たぶん計算量は $O(E + V \log V)$ かも

## 必要なライブラリ
[Graph](https://oxojo.github.io/Oxojo-Library/Graph/Graph)

## つかいかた
```
MST T = Prim(G)
```
合計コストと、最小全域木をなす辺集合が返ってくる

## 実装
[Prim.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Prim.cpp)
```cpp
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
```

## Verify
[AOJ_GRL_2_A](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A)
```cpp
void solve() {
	ll V, E; cin >> V >> E;
	Graph G(V);
	for (ll i = 0; i < E; i++) {
		ll s, t, w; cin >> s >> t >> w;
		G.add(s, t, w);
	}
	MST mst = Prim(G);
	cout << mst.cost << endl;
}
```
