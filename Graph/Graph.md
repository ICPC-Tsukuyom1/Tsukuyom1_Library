# Graph

## なにこれ
グラフ

## 使い方
### 宣言
```
Graph G(N);
```
$N$ はグラフの頂点数

### 辺の追加
```
G.add(from, to, cost, direct);
```
from : 始点<br>
to : 終点<br>
cost : 辺の重み（省略可、default は 1）<br>
direct : 有向辺か（省略可、default は false）

## 実装
[Graph.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/Graph.cpp)
```cpp
struct Edge {
    ll from, to, cost;
    Edge (ll from, ll to, ll cost = 1ll) : from(from), to(to), cost(cost) {}
};
struct Graph {
    vector<vector<Edge>> G;
    Graph() = default;
    explicit Graph(ll N) : G(N) {}
    size_t size() const {
        return G.size();
    }
    void add(ll from, ll to, ll cost = 1ll, bool direct = 0) {
        G[from].emplace_back(from, to, cost);
        if (!direct) G[to].emplace_back(to, from, cost);
    }
    vector<Edge> &operator[](const int &k) {
        return G[k];
    }
};
using Edges = vector<Edge>;
```
