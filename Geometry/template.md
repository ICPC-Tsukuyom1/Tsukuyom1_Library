# template

## なにこれ
幾何ライブラリのテンプレートで、点・線分・円などの構造体を定義しています

## 使い方
### 点の宣言
```
Point p(x, y);
```
座標を指定して宣言します<br>
<br>
この構造体では、ベクトル和・ベクトル差・スカラー倍・スカラー除算・大小比較( ```<``` のみ)・等値判定が実装されています

### 線分の宣言
```
Segment s(a, b);
```
線分の両端 2 点を指定して宣言します<br>
直線の宣言も一応は可能です（通る 2 点を指定すればよいので）

### 円の宣言
```
Circle c(C, r);
```
円の中心と半径を指定して宣言します

### 他
```
Vector v(x, y);
```
ベクトルです　宣言方法は点と同じ<br>

```
Line L(a, b);
```
直線です　宣言方法は線分と同じ

```
Polygon P(N);
```
多角形（＝点集合）です ```vector<Point>``` と一緒なので、それと同じように宣言してあげればよいです

## 実装
[template.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.cpp)
```cpp
#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS)
class Point {
public:
    ld x;
    ld y;

    Point(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(ld a) { return Point(a * x, a * y); }
    Point operator/(ld a) { return Point(x / a, y / a); }

    ld abs() { return sqrt(norm()); }
    ld norm() { return x * x + y * y; }

    bool operator<(const Point& p) const {
        return !equals(x, p.x) ? x < p.x : y < p.y;
    }
    bool operator==(const Point& p) const {
        return fabs(x - p.x) < (1e-10) && fabs(y - p.y) < (1e-10);
    }
};
typedef Point Vector;
struct Segment {
    Point A;
    Point B;
};
typedef Segment Line;
class Circle {
public:
    Point C;
    ld r;
    Circle(Point C = Point(), ld r = 0.0) : C(C), r(r) {}
};
typedef vector<Point> Polygon;

```
