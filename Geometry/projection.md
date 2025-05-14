# ✅射影

## なにこれ
点から直線へ下ろした垂線の足の座標を求める。

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md) <br>
[dot_cross](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/dot_cross.md)

## 使い方
```
q = Projection(s, p);
```
s は Segment(Line), p は Point<br>
返り値は Point 型

## 実装
[projection.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/projection.cpp)
```cpp
Point Projection(Segment S, Point p) {
    Vector base = S.B - S.A;
    ld r = dot(p - S.A, base) / base.norm();
    return S.A + base * r;
}
```

## Verify
[AOJ_CGL_1_A](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A)
```cpp
void solve() {
	Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    Line L = {p1, p2};
    ll Q; cin >> Q;
    while (Q--) {
      Point p; cin >> p.x >> p.y;
      Point x = Projection(L, p);
      cout << fixed << setprecision(12) << x.x << ' ' << x.y << endl;
    }
}
```
