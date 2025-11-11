#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 重み付きUnionFind

*なにこれ*

WeightedUnionFind は、頂点の連結状態と重みを管理するデータ構造。

#sourcecode(```cpp
wuf.merge(a, b, w);
```)

(bの重み) - (aの重み) = w になります

*連結判定*

#sourcecode(```cpp
wuf.connected(u, v);
```)

連結していたら true が返ってきます

*重みの差*

#sourcecode(```cpp
wuf.diff(a, b)
```)

(bの重み) - (aの重み)を返します

*グループの要素数*

#sourcecode(```cpp
wuf.size(i)
```)

#sourcefile(read("../Structure/weightedunionfind.cpp"), lang: "cpp")
