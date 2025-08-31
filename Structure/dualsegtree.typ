#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Dual Segment Tree

双対セグメント木。structの定義の直前に、`using`、`define`、または関数定義を用いて `F`、`id`、`merge` を定義してください。

(実践での利用においては、structを写経しながら該当部分を編集してもらっても構いません)

- `F` : 演算の型
- `F id` : 単位元
- `merge(F a, F b) -> F` : 演算。`merge(a, b)(x) = b(a(x))` となるように (a, bが時系列順になるように) 指定してください。

区間和・区間一次関数適用
#sourcecode(```cpp
#define F pair<mint, mint>
#define id F{1, 0}
#define merge(a, b) F{a.first * b.first, a.second * b.first + b.second}
```)

#sourcefile(read("../Structure/dualsegtree.cpp"), lang: "cpp")