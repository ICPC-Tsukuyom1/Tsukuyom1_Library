// depends on: Point
ld arg(Point p, Point q) { return atan2(p.cross(q), p.dot(q)); }
ld fac(Circle c, Polygon ps) {
  auto tri = [&](Point p, Point q) {
    ld r2 = c.r * c.r / 2.0;
    Point d = q - p;
    auto a = d.dot(p) / d.norm(), b = (p.norm() - c.r * c.r) / d.norm();
    auto det = a * a - b;
    if (sign(det) <= 0) return arg(p, q) * r2;
    auto s = -a - sqrtl(det), t = -a + sqrtl(det);
    if (sign(s) < 0) s = ld(0);
    if (sign(t - 1) > 0) t = ld(1);
    if (sign(t) < 0 || sign(s - 1) >= 0) return arg(p, q) * r2;
    Point u = p + d * s, v = p + d * t;
    return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
  };
  auto sum = 0.0;
  rep(i, sz(ps)) { sum += tri(ps[i] - c.c, ps[(i + 1) % sz(ps)] - c.c); }
  return sum;
}