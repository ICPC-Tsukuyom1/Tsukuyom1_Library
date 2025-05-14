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
