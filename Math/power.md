# $n^m$ mod $p$
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Math/power.cpp)

## なにこれ
べき乗を mod $p$ で求める　 $O(\log m)$ のはず

## 使い方
```
a = power(n, m, p);
```
n : 底<br>
m : 指数<br>
p : 余りを取る数<br>
返り値： $n^m$ mod $p$
