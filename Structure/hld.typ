#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== HLD

木のパス・または頂点上に値を載せ、特定のパス上に対しての区間演算が可能なデータ構造です。
SegTreeなどの区間操作が可能なデータ構造と合わせて使うことが想定されています。

例えば、パス上の頂点 (両端含む) の値の総和を求めるためには、

#sourcecode(```cpp
HLD hld(g);
BIT bit(n);

// 頂点 p に値 x をセット
hld.add(p, p, [&](int l, int r) { bit.apply(l, x); });

// パスuv上の頂点の値の総和を取得
hld.query(
  u, v, 0LL, [&](ll l, ll r) { return bit.prod(l, r); },
  [](ll a, ll b) { return a + b; }
)
```)

#sourcefile(read("../Structure/hld.cpp"), lang: "cpp")