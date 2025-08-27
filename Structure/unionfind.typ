#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== UnionFind

*なにこれ*

UnionFind は、頂点の連結状態を管理するつよそうなデータ構造。

*使い方*

*宣言*

#sourcecode(```cpp
UnionFind uf(N);
```)

*連結*

#sourcecode(```cpp
uf.unite(u, v);
```)

*連結判定*

#sourcecode(```cpp
uf.same(u, v);
```)

連結していたら true が返ってきます

*連結成分の個数*

#sourcecode(```cpp
uf.count()
```)

#sourcefile(read("../Structure/unionfind.cpp"), lang: "cpp")
