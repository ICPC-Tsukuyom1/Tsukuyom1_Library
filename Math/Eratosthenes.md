# エラトステネスの篩
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Math/Eratosthenes.cpp)

## なにこれ
$N$ 以下の素数の個数を、前処理 $O(N \log \log N)$ 各クエリ $O(1)$ で行います。

## つかいかた
### 宣言
```
Eratosthenes E(N);
```
宣言と同時に前処理が行われます。

### クエリ
```
c = E.count(n);
```
n 以下の素数の個数が返ってきます。
