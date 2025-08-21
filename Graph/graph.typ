#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Graph

*なにこれ*

グラフ

*使い方*

宣言

#sourcecode(```cpp
Graph G(N);
```)

$N$ はグラフの頂点数

*辺の追加*

#sourcecode(```cpp
G.add(from, to, cost, direct);
```)

from : 始点

to : 終点

cost : 辺の重み（省略可、default は 1）

direct : 有向辺か（省略可、default は false）

#sourcefile(read("../Graph/Graph.cpp"), lang: "cpp")