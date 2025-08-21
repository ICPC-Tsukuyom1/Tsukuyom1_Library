#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== オイラーの $phi$ 関数

*なにこれ*

$phi(n)$ は、 $n$ 以下の整数のうち $n$ と互いに素なものの個数を返す関数。

*使い方*

#sourcecode(```cpp
m = Euler_phi(n);
```)

#sourcefile(read("../Math/Euler_phi.cpp"), lang: "cpp")
