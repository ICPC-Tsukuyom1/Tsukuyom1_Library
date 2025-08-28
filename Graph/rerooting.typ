#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 全方位木DP (Rerooting)

function定義の前に、以下のように必要な情報を定義してください。

- `V` : 頂点 (実際には、その頂点を根とする部分木) に乗せる値の型
- `E` : 部分木に辺を追加したものに乗せる値の型 (モノイド)
- `put_edge(V, Edge) -> E` : `Edge` は `E` ではなくGraphテンプレートのもの
- `put_vert(E, int) -> V` : intは頂点のindex
- `op(E, E) -> E` : モノイドの演算
- `E ee` : モノイドの単位元

#sourcecode(```cpp
#define V pair<mint, ll>
#define E pair<mint, ll>
#define put_edge(v, edge) E{v.first * edge.cost.first + edge.cost.second * v.second, v.second}
#define put_vert(e, i) V{e.first + a[i], e.second + 1}
#define op(a, b) E{a.first + b.first, a.second + b.second}
#define ee E{0, 0}
```)

#sourcefile(read("../Graph/rerooting.cpp"), lang: "cpp")