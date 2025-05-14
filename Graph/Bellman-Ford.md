# ✅Bellman-Ford 法

## 概要
Bellman-Ford 法<br>
負の辺を含むグラフ上でも動く、単一始点最短経路問題を解くアルゴリズム。計算量は $O(EV)$ 

## 必要なライブラリ
[Graph](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Graph.md)

## 使い方
```
vector<ll>dist = bellman_ford(edges, V, s);
```
edges : 辺集合（**必要なのはグラフではなく辺の配列であることに注意**）<br>
V : 頂点数<br>
s : 始点<br>
<br>
返り値：始点 s から各頂点への最短距離を持つ長さ V の配列を返す

## 実装
[Bellman-Ford.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Bellman-Ford.cpp)
```cpp
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
```

## verify
[AOJ GRL_1_B](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B)
```cpp
void solve() {
	ll V, E; cin >> V >> E;
	ll s; cin >> s;
	Edges es;
	for (ll i = 0; i < E; i++) {
		ll from, to, cost;
		cin >> from >> to >> cost;
		es.emplace_back(from, to, cost);
	}
	vector<ll>dist = bellman_ford(es, V, s);
	if (dist.empty()) {
		cout << "NEGATIVE CYCLE" << endl;
		return;
	}
	for (ll i = 0; i < V; i++) {
		if (dist[i] == INF) {
			cout << "INF" << endl;
		}
		else cout << dist[i] << endl;
	}
}
```
