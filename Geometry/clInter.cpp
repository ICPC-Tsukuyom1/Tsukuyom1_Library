#include "projection.cpp"
const ld inf = numeric_limits<ld>::max() / 2;
pair<Point, Point> clInter(Circle c, Line l) {
  ld dd = (l.e - l.s).cross(c.c - l.s) / (l.e - l.s).abs();
  ll sgn = sign(dd - c.r);
  if (sgn > 0) {
    Point no = Point(-inf, -inf);
    return make_pair(no, no);
  } else {
    Point p = Projection(l, c.c, false);
    if (sgn == 0) { return make_pair(p, p); }
    Vector v = (l.e - l.s).unit();
    ld d = sqrtl(c.r * c.r - dd * dd);
    Point a = p + v * d, b = p - v * d;
    if (!(a < b)) swap(a, b);
    return make_pair(a, b);
  }
}