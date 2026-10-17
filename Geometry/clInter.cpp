/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/clInter.cpp */
// depends on: Point, projection
pair<Point, Point> clInter(Circle c, Line l) {
  Vector base = l.e - l.s;
  if (base.abs() < EPS) return make_pair(Point(-inf, -inf), Point(-inf, -inf));
  ld dd = fabs(base.cross(c.c - l.s) / base.abs());
  ll sgn = sign(dd - c.r);
  if (sgn > 0) {
    Point no = Point(-inf, -inf);
    return make_pair(no, no);
  } else {
    Point p = Projection(l, c.c, false);
    if (sgn == 0) { return make_pair(p, p); }
    Vector v = base.unit();
    ld d = sqrtl(max((ld)0, c.r * c.r - dd * dd));
    Point a = p + v * d, b = p - v * d;
    if (!(a < b)) swap(a, b);
    return make_pair(a, b);
  }
}
