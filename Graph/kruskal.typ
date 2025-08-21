#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== クラスカル法

*なにこれ*

最小全域木を、辺に注目して構築する。計算量は $O(E log E)$ だった記憶がある

*必要なライブラリ*

- Graph
- UnionFind

*つかいかた*

#sourcecode(```cpp
MST E = Kruskal(es, V);
```)

es は辺集合、V は頂点数

合計コストと最小全域木をなす辺集合が返ってくる

#sourcefile(read("../Graph/Kruskal.cpp"), lang: "cpp")