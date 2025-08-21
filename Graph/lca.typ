#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 最小共通祖先

*なにこれ*

最小共通祖先を求める。2 頂点 $u, v$ について、2 頂点から最も近い祖先を $"lca"(u, v)$ とする。

*必要なライブラリ*

- Graph

*つかいかた*

宣言

#sourcecode(```cpp
LCA lca(G);
```)

前処理

#sourcecode(```cpp
lca.build();
```)

計算量は覚えていません

query

#sourcecode(```cpp
ll p = lca.query(u, v);
```)

$O(log V)$ だった記憶があります　 $"lca"(u, v)$ を返す

#sourcefile(read("../Graph/lca.cpp"), lang: "cpp")