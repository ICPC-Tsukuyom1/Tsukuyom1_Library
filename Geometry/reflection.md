# ✅反射

## なにこれ
直線に関して点と対称な点を返します　点から射影へのベクトルを 2 倍するだけなので実質 Projection

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md) <br>
[Projection](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/projection.md)

## 使い方
```
q = Projection(s, p);
```

## 実装
[reflection.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/reflection.cpp)
```cpp
Point Reflection(Segment S, Point p) {
    return p + (Projection(S, p) - p) * 2.0;
}
```

## Verify
[AOJ_CGL_1_B](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_B)
```cpp
void solve() {
	Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    Line L = {p1, p2};
    ll Q; cin >> Q;
    while (Q--) {
      Point p; cin >> p.x >> p.y;
      Point x = Reflection(L, p);
      cout << fixed << setprecision(12) << x.x << ' ' << x.y << endl;
    }
}
```
