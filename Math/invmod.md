## 逆元
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Math/invmod.cpp)

## なにこれ
$\cfrac{1}{n}$ mod $p$ を求める。gcd(n, p) = 1 のとき assert に引っかかるので注意。

## 必要なライブラリ
[拡張ユークリッド互除法](https://github.com/Oxojo/Oxojo-Library/blob/main/Math/extgcd.cpp)

## 使い方
```
inv = invmod(n, p)
```
