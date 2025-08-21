#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 二項係数

*なにこれ*

二項係数 $binom(n, k) "mod" p$

*使い方*

制約によって分けられます

*デカい版*

$k <= n <= 10^7, p$ が素数のとき

#sourcecode(```cpp
init();
c = com(n, k);
```)

init() : 初期化（階乗や階乗の逆元を求めておく） $O(N)$

com(n, k) : 計算 $O(1)$

*小さい版*

$k <= n <= 2000, p$ が*正整数*のとき（素数でなくても良い）

#sourcecode(```cpp
calc();
c = C[n][k];
```)

calc() : 計算（パスカルの三角形） $O(N^2)$

配列 C に二項係数が格納されています $C_(n,k) = binom(n, k)$

#sourcefile(read("../Math/binomial-coefficients.cpp"), lang: "cpp")
