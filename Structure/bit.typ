#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== BIT (Binary Indexed Tree)

2024/06/18 更新しました

*なにこれ*

BIT です

一点更新・区間和クエリを処理できます

*使い方*

*宣言*

#sourcecode(```cpp
BIT bit(N);
```)

N : 要素数
配列を引数にしてもよいです

*更新*

#sourcecode(```cpp
bit.apply(i, x);
```)

i : 更新する場所（0-indexed）

x : 更新に使う値 ($a_i := a_i + x$ と更新します)

*クエリ*

#sourcecode(```cpp
s = bit.prod(i);
```)

0-indexed の position $i$ に対し、 $sum_(k=1)^(i-1) a_k$ を返します

区間 [l, r) を引数にすることで、その範囲の sum を得ることができます

*二分探索*

#sourcecode(```cpp
ll l = bit.lower_bound(x);
```)

lower_bound, upper_bound が使えます

#sourcefile(read("../Structure/BIT.cpp"), lang: "cpp")
