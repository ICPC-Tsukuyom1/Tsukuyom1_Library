#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 木の直径

重み付き木(辺の重みは非負)の直径、すなわち任意の 2 頂点間パスの重み和の最大値を、2 回の DFS で
$O(V)$ で求める。

使い方: `TreeDiameter td(n)` → `td.add_edge(u, v, w)`(無向辺) → `td.diameter()`。最遠点も得たい場合は
`td.farthest(s)` が (距離, 頂点) を返す。

DFS は明示スタックの反復実装のため、深い木(パス状 $n approx 3 times 10^5$ など)でもスタックオーバーフローしない。

#sourcefile(read("../Graph/tree-diameter.cpp"), lang: "cpp")
