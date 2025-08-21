#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Dijkstra法

*なにこれ*

ダイクストラ法は、非負の重み付きグラフに対し、単一始点最短経路問題を $O(E log V)$ で解く。

*必要なライブラリ*

- Graph

*使い方*

#sourcecode(```cpp
dijkstra(G, s, dis);
```)

dis に、始点から各頂点への最短距離が格納される。

#sourcefile(read("../Graph/dijkstra.cpp"), lang: "cpp")