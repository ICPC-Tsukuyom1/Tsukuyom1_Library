# 凸性判定

## なにこれ
多角形が凸かどうかを判定します。

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md) <br>
[ccw](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/ccw.md)

## 使い方
```
check = isconvex(S)
```
S : Polygon 型

## 実装
[isconvex.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md)
```cpp
bool isconvex(Polygon S) {
    bool check = true;
    for (ll i = 0; i+1 < S.size(); i++) {
        if (ccw(S[i],S[(i+1)%(ll)S.size()],S[(i+2)%(ll)S.size()]) == COUNTER_CLOCKWISE) {
            check = false;
        }
    }
    bool check2 = true;
    for (ll i = 0; i+1 < S.size(); i++) {
        if (ccw(S[i],S[(i+1)%(ll)S.size()],S[(i+2)%(ll)S.size()]) == CLOCKWISE) {
            check2 = false;
        }
    }
    return check | check2;
}
```

## Verify
[AOJ_CGL_3_B](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_B)
```cpp
void solve() {
  ll N; cin >> N;
  Polygon S(N);
  for (ll i = 0; i < N; i++) {
    cin >> S[i].x >> S[i].y;
  }
  cout << isconvex(S) << endl;
}
```
