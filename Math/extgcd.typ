#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 拡張ユークリッド互除法

*なにこれ*

ユークリッドの互除法みたいな雰囲気で、 $a x + b y = c$ を解く。

*使い方*

#sourcecode(```cpp
c = extgcd(a, b, x, y);
```)

これにより x, y が編集される。c は基本的に gcd(a, b) になる。

#sourcefile(read("../Math/extgcd.cpp"), lang: "cpp")
