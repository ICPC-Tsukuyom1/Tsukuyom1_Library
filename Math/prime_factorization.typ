#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 素因数分解

*なにこれ*

素因数分解をする

*使い方*

#sourcecode(```cpp
A = prime_factorization(n)
```)

n : 素因数分解する整数

返り値： $n = p_1^(k_1)p_2^(k_2) dots.h.c p_m^(k_m)$ のとき、 $a_i = (p_i, k_i)$ の pair 配列を返す

#sourcefile(read("../Math/prime-factorization.cpp"), lang: "cpp")
