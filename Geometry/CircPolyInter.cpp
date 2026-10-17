/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/CircPolyInter.cpp */
// depends on: Point
ld arg(Point p, Point q) { return atan2l(p.cross(q), p.dot(q)); }
ld fac(Circle c, Polygon ps) {
  auto tri = [&](Point p, Point q) {
    ld r2 = c.r * c.r / 2;
    Point d = q - p;
    ld dn = d.norm();
    if (dn == 0) return arg(p, q) * r2;
    ld a = d.dot(p) / dn, b = (p.norm() - c.r * c.r) / dn;
    ld det = a * a - b;
    if (sign(det) <= 0) return arg(p, q) * r2;
    ld s = -a - sqrtl(det), t = -a + sqrtl(det);
    if (sign(s) < 0) s = 0;
    if (sign(t - 1) > 0) t = 1;
    if (sign(t) < 0 || sign(s - 1) >= 0) return arg(p, q) * r2;
    Point u = p + d * s, v = p + d * t;
    return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
  };
  ld sum = 0;
  rep(i, sz(ps)) { sum += tri(ps[i] - c.c, ps[(i + 1) % sz(ps)] - c.c); }
  return sum;
}
