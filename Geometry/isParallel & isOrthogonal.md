# ✅平行・直交

## 概要
2 直線が平行・直交であるかどうかを判定する。

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md)<br>
[dot_cross](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/dot_cross.md)

## 使い方
基本的には、Segment(Line) 型を引数にする。ただし、場合に応じて、Vector(=Point) 型の引数 2 つを取る場合や、Point 型の引数 4 つを取る場合がある。<br>

### Segment(Line) 型の場合
```
check1 = isParallel(s1, s2);
check2 = isOrthogonal(s1, s2);
```
2 線分(直線) $s_1, s_2$ の平行・直交を判定する。

### Vector 型の場合
```
check1 = isParallel(v1, v2);
check2 = isOrthogonal(v1, v2);
```
2 ベクトル $v_1, v_2$ の平行・直交を判定する。

### Point 型の場合
```
check1 = isParallel(p1, p2, p3, p4);
check2 = isOrthogonal(p1, p2, p3, p4);
```
2 直線 $p_1 p_2,\ p_3 p_4$ の平行・直交を判定する。

### 実装
[isParallel.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/isParallel.cpp)
[isOrthogonal.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/isOrthogonal.cpp)
```cpp
bool isParallel(Vector A, Vector B) {
    return equals(cross(A, B), 0.0);
}
bool isParallel(Point A1, Point A2, Point B1, Point B2) {
    return isParallel(A1 - A2, B1 - B2);
}
bool isParallel(Segment S1, Segment S2) {
    return equals(cross(S1.B - S1.A, S2.B - S2.A), 0.0);
}
bool isOrthogonal(Vector A, Vector B) {
    return equals(dot(A, B), 0.0);
}
bool isOrthogonal(Point A1, Point A2, Point B1, Point B2) {
    return isOrthogonal(A1 - A2, B1 - B2);
}
bool isOrthogonal(Segment S1, Segment S2) {
    return equals(dot(S1.B - S1.A, S2.B - S2.A), 0.0);
}
```

## Verify
[AOJ_CGL_2_A](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_A)
```cpp
void solve() {
  Point p1, p2, p3, p4;
  cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
  Line s1 = {p1, p2}, s2 = {p3, p4};
  if (isParallel(s1, s2)) { cout << 2 << endl; }
  else if (isOrthogonal(s1, s2)) { cout << 1 << endl; }
  else cout << 0 << endl;
}
```
