#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== SegTree

セグメント木。
structの定義の直前に、`using`、`define`、または関数定義を用いて `T`、`e`、`op` を定義してください。

(実践での利用においては、structを写経しながら該当部分を編集してもらっても構いません)

- `T` : 値の型
- `T e` : opの単位元
- `op(T a, T b) -> T` : 演算。`a`、`b` はこの順で隣接していることが保証される。

区間和
#sourcecode(```cpp
#define T ll
#define e 0
#define op(a, b) a+b
```)

区間Min
#sourcecode(```cpp
#define T ll
#define e INF
#define op(a, b) min(a, b)
```)

一次関数の合成
#sourcecode(```cpp
#define T pair<mint, mint>
#define e {1, 0}
#define op(a, b) {a.first * b.first, a.second * b.first + b.second}
```)

#sourcefile(read("../Structure/segtree.cpp"), lang: "cpp")
