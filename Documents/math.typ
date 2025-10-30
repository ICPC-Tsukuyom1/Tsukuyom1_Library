#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 数学

=== 素数の個数
#table(
  columns: (auto, auto, auto, auto, auto, auto),
  inset: 10pt,
  align: horizon,
  table.header(
    [$n$], [$10^5$], [$10^6$], [$10^7$], [$10^8$], [$10^9$]
  ),
  [$pi(n)$], [9592], [78498], [664579], [5.76e+6], [5.08e+7]
)

=== 高度合成数
#table(
  columns: (auto, auto, auto, auto, auto, auto, auto),
  inset: 10pt,
  align: horizon,
  table.header(
    [$<=n$], [$10^6$], [$10^7$], [$10^8$], [$10^9$], [$10^10$], [$10^11$]
  ),
  [d(x)], [240], [448], [768], [1344], [2304], [4032]
)
#table(
  columns: (auto, auto, auto, auto, auto, auto, auto),
  inset: 10pt,
  align: horizon,
  table.header(
    [$<=n$], [$10^12$], [$10^13$], [$10^14$], [$10^15$], [$10^16$], [$10^17$]
  ),
  [d(x)], [6720], [10752], [17280], [26880], [41472], [64512]
)

=== 母関数

$1/(1-x) = 1 + x + x^2 + ... = sum_(n=0)^infinity x^n$

$1/(1-x)^2 = 1 + 2x + 3x^2 + ... = sum_(n=0)^infinity (n+1)x^n$

$1/(1-x)^3 = 1 + 3x + 6x^2 + ... = sum_(n=0)^infinity 1/2(n+1)(n+2)x^n$

$1/(1-x)^d = sum_(n=0)^infinity vec(n+d-1, n) x^n$

$sqrt(1-x) = 1 - 1/2 x - 1/8 x^2 - ... = 1 - sum_(n=1)^infinity (2n-2)!/(2^(2n-1)n!(n-1)!) x^n$

$1/(sqrt(1-x)) = 1 + 1/2 x + 3/8 x^2 + ... = sum_(n=0)^infinity (2n)!/(4^n n!) x^n$

$(1-sqrt(1-4x))/(2x) = sum_(n=0)^infinity C_n x^n = sum_(n=0)^infinity (2n)!/((n+1)!n!)x^n$ (カタラン数)

$1/(sqrt(1-4x)) = sum_(n=0)^infinity vec(2n, n) x^n$

$1/(1-x-x^2) = 1 + x + 2x^2 + ... = sum_(n=0)^infinity F_n x^n$ (フィボナッチ数)

$log(1-x) = -x - 1/2 x^2 - 1/3 x^3 - ... = sum_(n=1)^infinity 1/n x^n$

$exp(exp x-1) = sum_(n=0)^infinity B_n x^n/n$ (ベル数の EGF)

$1/k (exp x-1)^k = sum_(n=0)^infinity S(n, k) x^n/n!$ (第二種スターリング数)

$(exp(-x))/(1-x) = sum_(n=0)^infinity a_n x^n/n!$ (モンモール数)

$C(x)^k = ((1-sqrt(1-4x))/(2x))^k = sum_(n = 0)^infinity k/(n + k) vec(2n + k - 1, n)$ (カタラン数の母関数の累乗)

$product_(n=1)^infinity 1/(1-x^n) = sum_(n=0)^infinity P_n x^n$ (分割数)