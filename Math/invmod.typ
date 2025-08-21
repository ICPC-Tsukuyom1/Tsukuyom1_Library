#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 逆元

*なにこれ*

$\cfrac{1}{n}$ mod $p$ を求める。gcd(n, p) = 1 のとき assert に引っかかるので注意。

*必要なライブラリ*

- 拡張ユークリッド互除法

*使い方*

#sourcecode(```cpp
inv = invmod(n, p)
```)

#sourcefile(read("../Math/invmod.cpp"), lang: "cpp")
