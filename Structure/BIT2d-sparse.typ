#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 2次元 BIT (sparse)

座標圧縮した平面上で、点加算と矩形和を $O(log^2 q)$ で処理する 2 次元 BIT。座標が大きくてもメモリ $O(q log q)$ で済む(`BIT2d` は $O(H W)$ 必要なため、$10^9$ 級の座標ではこちらを使う)。

入力で現れる点座標とクエリ境界を先に `request`(点更新)/ `request_prefix`(矩形クエリの境界)で登録し、`build()` を呼んでから `add` / `sum` を使う。矩形は 0-indexed 半開区間 $[x_1, x_2) × [y_1, y_2)$。

#sourcefile(read("../Structure/BIT2d-sparse.cpp"), lang: "cpp")
