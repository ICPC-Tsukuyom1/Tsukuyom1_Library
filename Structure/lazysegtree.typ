#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Lazy Segment Tree

遅延セグメント木。structの定義の直前に、`using`、`define`、または関数定義を用いて `T`、`e`、`F`、`id`、`op`、`merge`、`apply` を定義してください。

(実践での利用においては、structを写経しながら該当部分を編集してもらっても構いません)

- `T` : 値の型
- `T e` : opの単位元
- `F` : 演算の型
- `F id` : mergeの単位元
- `op(T a, T b) -> T` : 演算。`a`、`b` はこの順で隣接していることが保証される。
- `merge(F a, F b) -> F` : 演算。`merge(a, b)(x) = b(a(x))` となるように (a, bが時系列順になるように) 指定してください。
- `apply(F f, T x, ll l) -> T` : 演算。`l` は区間の長さを表します。

区間和・区間一次関数適用
#sourcecode(```cpp
#define T mint
#define e 0
#define F pair<mint, mint>
#define id F{1, 0}
#define op(a, b) a+b
#define merge(a, b) F{a.first * b.first, a.second * b.first + b.second};
#define apply(f, x, l) f.first * x + f.second * l;
```)

なおDynamic Lazy Segment Treeとして実装されているので、構築 $O(1)$ 、クエリ $O(log N)$ です。( $N = 10^18$ でも動作します)

#sourcefile(read("../Structure/lazysegtree.cpp"), lang: "cpp")