# ✅Warshall-Floyd 法
~~これライブラリいらなくない？~~

## なにこれ
全点対間最短距離問題を解く。 $O(N^3)$

## 使い方
```
Warshall_Floyd(dist, V);
```
V は頂点数。dist に任意の点対についての最短距離が格納される。

## 実装
[Warshall_Floyd.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Warshall_Floyd.cpp)
```cpp
void Warshall_Floyd(vector<vector<ll>>&dist, ll N) {
  rep(k, N) {
    rep(i, N) {
      rep(j, N) {
        if (dist[i][k] == INF || dist[k][j] == INF) continue;
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}
```

## Verify
[AOJ_GRL_1_C](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C)
```cpp
void solve() {
  ll V, E; cin >> V >> E;
  vector<vector<ll>>dist(V,vector<ll>(V, INF));
  rep(i, V) {
    dist[i][i] = 0;
  }
  rep(i, E) {
    ll u, v, d; cin >> u >> v >> d;
    dist[u][v] = d;
  }
  Warshall_Floyd(dist, V);
  rep(i, V) {
    if (dist[i][i] < 0) {
      cout << "NEGATIVE CYCLE" << endl;
      return;
    }
  }
  rep(i, V) {
    rep(j, V) {
      if (j != 0) cout << ' ';
      if (dist[i][j] == INF) cout << "INF";
      else cout << dist[i][j];
    }
    cout << endl;
  }
}
```
