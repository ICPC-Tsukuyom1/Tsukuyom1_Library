// depends on: Point
pair<bool, Point> lineInter(Line l1, Line l2) {
  auto d = (l1.e - l1.s).cross(l2.e - l2.s);
  if (!sign(d)) return {-eq(l1.s.cross(l1.e, l2.s), (ld)0), Point(0, 0)};
  auto p = l2.s.cross(l1.e, l2.e), q = l2.s.cross(l2.e, l1.s);
  return {1, (l1.s * p + l1.e * q) / d};
}