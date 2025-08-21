#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== トポロジカルソート

*なにこれ*

トポロジカルソートをします

DAG について、ある頂点の子が全て自身より後に来るように頂点を並べる

*必要なライブラリ*

- Graph

*使い方*

#sourcecode(```cpp
p = topological_sort(G)
```)

p は確かソートされた頂点を順番に格納した配列になるはず...

#sourcefile(read("../Graph/topological.cpp"), lang: "cpp")