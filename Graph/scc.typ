#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== SCC (強連結成分分解)

*なにこれ*

強連結成分分解を行う。$O(V + E)$

*必要なライブラリ*

- Graph

*使い方*

宣言

#sourcecode(```cpp
SCC scc(G);
```)

G : Graph

SCC 構築

#sourcecode(```cpp
scc.build(G);
```)

G : Graph

*G に SCC が構築されるので、ここに元のグラフは代入しない。*

#sourcefile(read("../Graph/SCC.cpp"), lang: "cpp")