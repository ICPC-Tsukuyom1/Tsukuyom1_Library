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

=== Lucas の定理
任意の素数 $p$ と非負整数 $m, n$ に対し、$m$ の $p$ 進数表示を $m_k m_(k-1) ... m_0$, $n$ の $p$ 進数表示を $n_k n_(k-1) ... n_0$ とすると

$
  ""_m "C"_n equiv product_(i=0)^(k) ""_(m_i) "C"_(n_i)
$

=== 多項係数
$
  vec(k_1 + ... + k_n, (k_1, k_2, ..., k_n)) = (sum k_i)!/(k_1 ! k_2 ! ... k_n !)
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

=== 第 1 種スターリング数
$c(n, k)$ : $1, 2, ..., n$ の順列で、巡回置換 $k$ 個に分割できるものの個数。$c(0, 0) = 1$
$
  c(n, k) = c(n - 1, k - 1) + (n - 1) c(n - 1, k)
$
$
  sum_(k=0)^n c(n, k) = n!
$
$
  sum_(k=0)^n 2^k c(n, k) = (n+1)!
$
$
  sum_(k=0)^n (-1)^k c(n,k) = 0
$
$
  sum_(k-0)^n c(n, k) x^k = x(x + 1)...(x + n - 1)
$
最後の式を用いて分割統治して、片方の計算を Polynomial Taylor Shift で再利用することで、$c(N, k)$ の $k$ に関する列挙が $O(N log N)$ 時間で行える。 


=== 第 2 種スターリング数
$S(n, k)$ : $1, 2, ..., n$ を $k$ 個の区別しない集合に分割する方法の数

$
  S(n, k) = S(n - 1, k - 1) + k S(n - 1, k)
$
$
  S(n, 1) = S(n, n) = 1
$
$
  S(n, k) = 1 / k! sum_(j=0)^k (-1)^(k - j) ""_k "C"_j j^n
$
最後の式と畳み込みを用いて、$S(N, k)$ の $k$ に関する列挙を $O(N log N)$ 時間で行える。

=== ベル数
$B(n, k)$ : $1, 2, ..., n$ を $k$ 個の集合に分割する方法の数
$
  B(n, k) = sum_(j=1)^k S(n, j) = sum_(j=1)^k 1/j! sum_(i=1)^j (-1)^(j-i) ""_j "C"_i i^n
$
$B_n = sum_(k=0)^(n) B(n, k)$ とすると、

$
  B_(n + 1) = sum_(k=0)^n ""_n "C"_k B_k B_n = 1/e sum_(k=0)^infinity k^n/(k!)
$
EGF を用いて、$B_0, ..., B_n$ の列挙が $O(N log N)$ 時間でできる。
=== 分割数
$n$ を $k$ 個の正の整数に分割する方法の数を $P(n,k)$ とすると、
$
  P(n, k) = P(n - k, k) + P(n - 1, k - 1)
$
$P_n = sum_(k=0)^n P(n, k)$ とすると、$product_(n=1)^infinity (1-x^n) = sum_(n=-infinity)^infinity (-1)^n x^(n(3n+1)/2)$ より、$P_0, ..., P_N$ を $O(N log N)$ 時間で列挙できる。

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