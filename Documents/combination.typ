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
  vec(m, n) equiv product_(i=0)^(k) vec(m_i, n_i)
$

=== 多項係数
$
  vec(k_1 + ... + k_n, (k_1, k_2, ..., k_n)) = (sum k_i)!/(k_1 ! k_2 ! ... k_n !)
$

=== Combination の関係式
$vec(n, k) = vec(n - 1, k - 1) + vec(n - 1, k), vec(n, k) = n/k vec(n - 1, k - 1), vec(L, k) + ... + vec(R - 1, k) = vec(R, k + 1) - vec(L, k + 1)$

- Vandermonde の畳み込み
$
sum_(k=0)^n vec(p, k) dot vec(q, n - k) = vec(p + q, n)
$

- ホッケースティック恒等式
$
  sum_(k=r)^n vec(k, r) = vec(n + 1, r + 1)
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
  S(n, k) = 1 / k! sum_(j=0)^k (-1)^(k - j) vec(k, j) j^n
$
最後の式と畳み込みを用いて、$S(N, k)$ の $k$ に関する列挙を $O(N log N)$ 時間で行える。

=== ベル数
$B(n, k)$ : $1, 2, ..., n$ を $k$ 個の集合に分割する方法の数
$
  B(n, k) = sum_(j=1)^k S(n, j) = sum_(j=1)^k 1/j! sum_(i=1)^j (-1)^(j-i) vec(j, i) i^n
$
$B_n = sum_(k=0)^(n) B(n, k)$ とすると、

$
  B_(n + 1) = sum_(k=0)^n vec(n, k) B_k B_n = 1/e sum_(k=0)^infinity k^n/(k!)
$
$
  B_(p^m + n) equiv m B_n + B_(n + 1) (mod p)
$

EGF (母関数リストに記載) を用いて、$B_0, ..., B_n$ の列挙が $O(N log N)$ 時間でできる。

=== 分割数
$n$ を $k$ 個の正の整数に分割する方法の数を $P(n,k)$ とすると、
$
  P(n, k) = P(n - k, k) + P(n - 1, k - 1)
$
$P_n = sum_(k=0)^n P(n, k)$ とすると、$product_(n=1)^infinity (1-x^n) = sum_(n=-infinity)^infinity (-1)^n x^(n(3n+1)/2)$ より、$P_0, ..., P_N$ を $O(N log N)$ 時間で列挙できる。

=== カタラン数
$
  C_n = 1/(n+1) vec(2n, n) = vec(2n, n) - vec(2n, n+1) = (2n)!/((n+1)!n!)
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
  [なし],[あり],[$vec(n+k-1, n)$],[$vec(k, n)$],[$vec(n-1, k-1)$],
  [あり],[なし],[$B(n, k)$],[$1$],[$S(n, k)$],
  [なし],[なし],[$P(n + k, k)$],[$1$],[$P(n, k)$],
)
ここで、$f(n, k) = sum_(i=1)^k (-1)^(k-i) vec(k, i) i^n$

=== ベルヌーイ数
EGF $x/(e^x - 1)$ (FFT-able) を用いたベルヌーイ数の定義 :
$
  f(x) = x/(e^x - 1) = sum_(n=0)^infinity B_n/(n!)x^n
$
漸化式 : 
$
  B_0 = 1, B_n = -1/(n+1) sum_(k=0)^(n-1) vec(n+1, k) B_k
$
$m$ 乗和を $O(m)$ で求められる :
$
  sum_(i=1)^m n^m = 1/(m+1) sum_(k=0)^m vec(m+1, k) B_k dot (n+1)^(m + 1 - k)
$