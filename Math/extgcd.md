# 拡張ユークリッド互除法
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Math/extgcd.cpp)

## なにこれ
ユークリッドの互除法みたいな雰囲気で、 $ax + by = c$ を解く。

## 使い方
```
c = extgcd(a, b, x, y);
```
これにより x, y が編集される。c は基本的に gcd(a, b) になる。
