#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Warshall-Floyd 法

#strike[これライブラリいらなくない？]

*なにこれ*

全点対間最短距離問題を解く。 $O(N^3)$

*使い方*

#sourcecode(```cpp
Warshall_Floyd(dist, V);
```)

V は頂点数。dist に任意の点対についての最短距離が格納される。

#sourcefile(read("../Graph/Warshall_Floyd.cpp"), lang: "cpp")