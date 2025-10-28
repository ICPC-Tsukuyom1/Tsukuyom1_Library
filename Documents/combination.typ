#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 組合せ論

=== モンモール数

長さ $n$ の攪乱行列 : $forall i = 1, ..., n$ について $i != p(i)$ の数は : 

$
D(n) = (n - 1)(D(n - 1) + D(n - 2)) = n D(n - 1) + (-1)^n
$

$
D(n) = n! sum_(k=0)^n (-1)^k / k! = floor(n!/e + 1/2)
$

=== Combination の関係式

- Vandermonde の畳み込み
$
sum_(k=0)^n ""_p "C"_k dot ""_q "C"_(n - k) = ""_(p + q) "C"_n
$

- ホッケースティック恒等式
$
  sum_(k=r)^n ""_k "C"_r = ""_(n + 1) "C"_(r + 1)
$

=== 第 2 種スターリング数
$
  S(n, k) = S(n - 1, k - 1) + k S(n - 1, k)
$
$
  S(n, 1) = S(n, n) = 1
$
$
  S(n, k) = 1 / k! sum_(j=0)^k (-1)^(k - j) ""_k "C"_j j^n
$

=== ベル数
$
  B(n, k) = sum_(j=1)^k S(n, j) = sum_(j=1)^k 1/j! sum_(i=1)^j (-1)^(j-i) ""_j "C"_i i^n
$

=== カタラン数
$
  C_n = 1/(n+1) ""_(2n) "C"_n = ""_(2n) "C"_n - ""_(2n) "C"_(n+1) = (2n)!/((n+1)!n!)
$
$
  C_0 = 1, C_(n + 1) = (2(2n+1))/(n+2)C_n, C_(n+1)=sum C_i C_(n-i)
$

=== 写像 12 相

$n$ 個の玉を $k$ 個の箱に分ける場合の数は、区別の有無に応じて次のようになる : 

#table(
  columns: (auto, auto, auto, auto, auto),
  inset: 10pt,
  align: horizon,
  table.header(
    [玉区別], [箱区別], [条件なし], [玉 1 つ以下], [玉 1 つ以上]
  ),
  [あり],[あり],[$k^n$],[$""_k "P"_n$],[$f(n, k)$],
  [なし],[あり],[$""_(n+k-1) "C"_n$],[$""_k "C"_n$],[$""_(n-1) "C"_(k-1)$],
  [あり],[なし],[$B(n, k)$],[$1$],[$S(n, k)$],
  [なし],[なし],[$P(n + k, k)$],[$1$],[$P(n, k)$],
)
ここで、$f(n, k) = sum_(i=1)^k (-1)^(k-i) ""_k "C"_i i^n$