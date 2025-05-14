# 多角形における点の包含

## なにこれ
多角形と点の位置関係を判定します。

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md) <br>
[dot_cross](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/dot_cross.md)

## 使い方
```
c = isinpolygon(p, S);
```
p : Point 型、S : Polygon 型 <br>
返り値は、0 : 点が多角形の外にある、1 : 点が多角形の辺上にある、2 : 点が多角形の内部にある　を示す。

## 実装
[isinpolygon.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/isinpolygon.cpp)
```cpp
int isinpolygon(Point p, Polygon S) {
    ll N = (ll)S.size();
    bool check = false;
    for (ll i = 0; i < N; i++) {
        Point A = S[i] - p, B = S[(i+1)%N] - p;
        if (abs(cross(A, B)) < EPS && dot(A, B) < EPS) return 1;
        if (A.y > B.y) swap(A, B);
        if (A.y < EPS && EPS < B.y && cross(A, B) > EPS) check = !check;
    }
    return (check ? 2 : 0);
}
```

## Verify
[AOJ_CGL_3_C](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_C)
```cpp
void solve() {
  ll N; cin >> N;
  Polygon S(N);
  for (ll i = 0; i < N; i++) {
    cin >> S[i].x >> S[i].y;
  }
  ll Q; cin >> Q;
  while (Q--) {
    Point x; cin >> x.x >> x.y;
    cout << isinpolygon(x, S) << endl;
  }
}
```
