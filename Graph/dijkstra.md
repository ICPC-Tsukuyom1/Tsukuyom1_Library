# ✅Dijkstra法

## なにこれ
ダイクストラ法は、非負の重み付きグラフに対し、単一始点最短経路問題を $O(E \log V)$ で解く。

## 必要なライブラリ
[Graph](https://oxojo.github.io/Oxojo-Library/Graph/Graph)

## 使い方
```
dijkstra(G, s, dis);
```
dis に、始点から各頂点への最短距離が格納される。

## 実装
```cpp
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
```

## verify
[AOJ GRL_1_A](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A)
```cpp
void solve() {
	ll V, E; cin >> V >> E;
	ll s; cin >> s;
	Graph G(V);
	rep(i, E) {
		ll from, to, cost; cin >> from >> to >> cost;
		G.add(from, to, cost, 1);
	}
	vector<ll>dist(V, INF);
	dijkstra(G, s, dist);
	rep(i, V) {
		if (dist[i] == INF) {
			cout << "INF" << endl;
		}
		else cout << dist[i] << endl;
	}
}
```
