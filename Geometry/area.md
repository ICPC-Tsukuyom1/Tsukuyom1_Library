# ✅面積

## なにこれ
多角形の面積を求めます　~~凸多角形でない場合、バグるかもしれないです~~ ←凸でなくてもバグらないことを確認しました

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md) <br>
[dot_cross](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/dot_cross.md)

## 使い方
```
s = Area(S);
```
引数は Polygon 型

## 実装
[area.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/area.cpp)
```cpp
ld Area(Polygon S) {
    if (S.size() < 3) return 0;
    ld ans = 0;
    Point O = S[0];
    for (ll i = 1; i + 1 < S.size(); i++) {
        Point A = S[i], B = S[i+1];
        Vector C = A-O;
        Vector D = B-O;
        ld area = cross(C, D) * 0.5;
        ans += area;
    }
    return ans;
}
```

### Verify
[AOJ_CGL_3_A](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_A)
```cpp
void solve() {
  ll N; cin >> N;
  Polygon S(N);
  for (ll i = 0; i < N; i++) {
    cin >> S[i].x >> S[i].y;
  }
  cout << fixed << setprecision(1) << Area(S) << endl;
}
```
