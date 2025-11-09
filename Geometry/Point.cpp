#define EPS (1e-10)
#define eq(a, b) (fabs((a) - (b)) < EPS)
ll sign(ld x) { return (x >= EPS) - (x <= -EPS); }
const ld pi = 3.141592653589793238;
struct Point {
  typedef Point P;
  ld x, y;
  Point(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(ld a) const { return P(a*x, a*y); }
  P operator/(ld a) const { return P(x/a, y/a); }
  ld abs() const { return sqrtl(norm()); }
  ld norm() const { return x * x + y * y; }
  bool operator<(const P& p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(const P& p) const { return eq(x, p.x) && eq(y, p.y); }
  ld dot(P p) const { return x*p.x + y*p.y; }
  ld cross(P p) const { return x*p.y - y*p.x; }
  ld cross(P a, P b) const { return (a-*this).cross(b-*this); }
  P unit() const { return *this/abs(); }
  P perp() const { return P(-y, x); }
  P normal() const { return perp()/abs(); }
  ld angle() const { return atan2(y, x); }
  P rotate(ld theta) const {
    return P(x * cosl(theta) - y * sinl(theta),
             x * sinl(theta) + y * cosl(theta));}
};
typedef Point Vector;
struct Segment { Point s, e; };
typedef Segment Line;
struct Circle {
  Point c; ld r;
  Circle(Point c=Point(), ld r=0.0) : c(c),r(r) {}
};
typedef vec<Point> Polygon;
