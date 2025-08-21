#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 素数判定

*なにこれ*

素数判定を $O(sqrt(N))$ でやる

*使い方*

#sourcecode(```cpp
check = isprime(n)
```)

n : 判定する整数

返り値：素数ならtrue, 素数でなければfalse

#sourcefile(read("../Math/isprime.cpp"), lang: "cpp")
