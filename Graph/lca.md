# 最小共通祖先
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/lca.cpp)

## なにこれ
最小共通祖先を求める。2 頂点 $u, v$ について、2 頂点から最も近い祖先を $lca(u, v)$ とする。

## 必要なライブラリ
[Graph](https://oxojo.github.io/Oxojo-Library/Graph/Graph)

## つかいかた
### 宣言
```
LCA lca(G);
```

### 前処理
```
lca.build();
```
計算量は覚えていません

### query
```
ll p = lca.query(u, v);
```
$O(\log V)$ だった記憶があります　 $lca(u, v)$ を返す
