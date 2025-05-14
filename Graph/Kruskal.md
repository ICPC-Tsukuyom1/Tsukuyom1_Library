# ✅クラスカル法

## なにこれ
最小全域木を、辺に注目して構築する。計算量は $O(E \log E)$ だった記憶がある

## 必要なライブラリ
[Graph](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Graph.md) <br>
[UnionFind](https://github.com/Oxojo/Oxojo-Library/blob/main/Structure/unionfind.md)

## つかいかた
```
MST E = Kruskal(es, V);
```
es は辺集合、V は頂点数<br>
合計コストと最小全域木をなす辺集合が返ってくる

## 実装
[Kruskal.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Kruskal.cpp)
```cpp
struct MST {
    ll cost;
    Edges edges;
};
MST Kruskal(Edges &edges, ll V) {
    sort(edges.begin(),edges.end(), [](Edge &a, Edge &b) {
        return a.cost < b.cost;
    });
    UnionFind uf(V);
    ll total = 0ll;
    Edges es;
    for (auto e : edges) {
        if (!uf.same(e.from, e.to)) {
            es.emplace_back(e);
            total += e.cost;
            uf.unite(e.from, e.to);
        }
    }
    return {total, es};
}
```

## Verify
[AOJ GRL_2_A](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A)
```cpp
void solve() {
	ll V, E; cin >> V >> E;
	Edges es;
	for (ll i = 0; i < E; i++) {
		ll s, t, w; cin >> s >> t >> w;
		es.emplace_back(s, t, w);
	}
	MST mst = Kruskal(es, V);
	cout << mst.cost << endl;
}
```
