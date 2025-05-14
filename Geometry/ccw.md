# ✅ccw

## なにこれ
3 点の位置関係を示す

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md) <br>
[dot_cross](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/dot_cross.md)

## 使い方
```
check = ccw(a, b, c);
```
返り値は<br>
1 : a, b, c の順に反時計回りになるようになってる<br>
-1 : a, b, c の順に時計回りになるようになってる<br>
2 : c, a, b の順で同一直線上にある<br>
-2 : a, b, c の順で同一直線上にある<br>
0 : a, c, b の順で同一直線状にある<br>
のいずれか。

## 実装
[ccw.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/ccw.cpp)
```cpp
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
int ccw(Point A, Point B, Point C) {
    Vector S = B - A, T = C - A;
    if (cross(S, T) > EPS) return COUNTER_CLOCKWISE;
    if (cross(S, T) < -EPS) return CLOCKWISE; 
    if (dot(S, T) < -EPS) return ONLINE_BACK; 
    if (S.norm() < T.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}
```

## Verify
[AOJ_CGL_1_C](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_C)
```cpp
void solve() {
	Point p0, p1;
  cin >> p0.x >> p0.y >> p1.x >> p1.y;
  ll Q; cin >> Q;
  while (Q--) {
    Point p2; cin >> p2.x >> p2.y;
    int c = ccw(p0, p1, p2);
    if (c == 1) { cout << "COUNTER_CLOCKWISE" << endl; }
    else if (c == -1) { cout << "CLOCKWISE" << endl; }
    else if (c == 2) { cout << "ONLINE_BACK" << endl; }
    else if (c == -2) { cout << "ONLINE_FRONT" << endl; }
    else cout << "ON_SEGMENT" << endl;
  }
}
```
