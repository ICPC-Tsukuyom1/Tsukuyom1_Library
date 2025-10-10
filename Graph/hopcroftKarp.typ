#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bipartite Matching

二部グラフの最大マッチングを hopcroftKarp で求める。$O(sqrt(V)E)$

使われている辺は、$"btoa"(i) != -1$ である $i$ について $i -> "btoa"(i)$ の辺

#sourcefile(read("../Graph/hopcroftKarp.cpp"), lang: "cpp")