#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Dijkstra

非負の重み付きグラフに対し、単一始点最短経路問題を $O(E log V)$ で解く。

#sourcefile(read("../Graph/dijkstra.cpp"), lang: "cpp")