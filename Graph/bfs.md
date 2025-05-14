# ✅BFS(幅優先探索)

## なにこれ
BFS<br>
計算量は $O(V + E)$ だと思います

## 必要なライブラリ
[Graph](https://oxojo.github.io/Oxojo-Library/Graph/Graph)

## 使い方
```
bfs(G, s, dist);
```
G : グラフ<br>
s : 始点<br>
dist : 始点からの距離を格納する配列<br>
<br>
返り値：なし　dist が編集される

## 実装
[bfs.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/bfs.cpp)
```
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
```

## Verify
[AOJ_ALDS1_11_C](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_11_C)
```cpp
void solve() {
	ll N; cin >> N;
    Graph G(N);
    for (ll i = 0; i < N; i++) {
        ll v; cin >> v;
        v--;
        ll k; cin >> k;
        while (k--) {
            ll u; cin >> u;
            u--;
            G.add(v, u, 1, 1);
        }
    }
    vector<ll>dist(N, INF);
    bfs(G, 0, dist);
    for (ll i = 0; i < N; i++) {
        cout << i + 1 << ' ' << (dist[i] == INF ? -1 : dist[i]) << endl;
    }
}
```
