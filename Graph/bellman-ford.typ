#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bellman-Ford 法

負の辺を含むグラフ上でも動く、単一始点最短経路問題を解くアルゴリズム。計算量は $O(E V)$

#sourcefile(read("../Graph/Bellman-Ford.cpp"), lang: "cpp")