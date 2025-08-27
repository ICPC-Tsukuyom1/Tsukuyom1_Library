#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== SegTree

セグメント木。第二引数にラムダ式または関数ポインタを渡してください。

区間和
#sourcecode(```cpp
SegTree<ll> seg(
  n,
  [](ll a, ll b) { return a + b; },
  0
);
```)

区間Min
#sourcecode(```cpp
SegTree<ll> seg(
  n,
  [](ll a, ll b) { return min(a, b); },
  INF
);
```)

一次関数の合成
#sourcecode(```cpp
using T = pair<mint, mint>;
SegTree<T> seg(
  n,
  [](T a, T b) { return T{a.first * b.first, a.second * b.first + b.second}; },
  T{1, 0}
);
```)

#sourcefile(read("../Structure/segtree.cpp"), lang: "cpp")
