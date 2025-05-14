# 二項係数
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Math/binomial-coefficients.cpp)

## なにこれ
二項係数 $\dbinom{n}{k}\mod p$<br>

## 使い方
制約によって分けられます
### デカい版
$k \leq n \leq 10^7, p$ が素数のとき
```
init();
c = com(n, k);
```
init() : 初期化（階乗や階乗の逆元を求めておく） $O(N)$<br>
com(n, k) : 計算 $O(1)$

### 小さい版
$k \leq n \leq 2000, p$ が**正整数**のとき（素数でなくても良い）<br>
```
calc();
c = C[n][k];
```
calc() : 計算（パスカルの三角形） $O(N^2)$<br>
配列 C に二項係数が格納されています $C_{n,k} = \dbinom{n}{k}$
