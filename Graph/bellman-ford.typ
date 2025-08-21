#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bellman-Ford 法

*概要*

Bellman-Ford 法

負の辺を含むグラフ上でも動く、単一始点最短経路問題を解くアルゴリズム。計算量は $O(E V)$

*必要なライブラリ*

- Graph

*使い方*

#sourcecode(```cpp
vector<ll>dist = bellman_ford(edges, V, s);
```)

edges : 辺集合（*必要なのはグラフではなく辺の配列であることに注意*）
V : 頂点数
s : 始点

返り値：始点 s から各頂点への最短距離を持つ長さ V の配列を返す

#sourcefile(read("../Graph/Bellman-Ford.cpp"), lang: "cpp")