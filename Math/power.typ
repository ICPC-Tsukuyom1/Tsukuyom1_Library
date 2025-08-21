#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== $n^m$ mod $p$

*なにこれ*

べき乗を mod $p$ で求める　 $O(log m)$ のはず

*使い方*

#sourcecode(```cpp
a = power(n, m, p);
```)

n : 底

m : 指数

p : 余りを取る数

返り値： $n^m$ mod $p$

#sourcefile(read("../Math/power.cpp"), lang: "cpp")
