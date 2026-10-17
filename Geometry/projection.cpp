/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/projection.cpp */
// depends on: Point
// reflect = false : 点から直線へ下した垂線の足
// reflect = true  : 直線に関して対称な点
Point Projection(Segment S, Point p, bool reflect) {
  Vector base = S.e - S.s;
  if (base.abs() < EPS) return S.s;
  ld r = (p - S.s).dot(base) / base.norm();
  if (reflect) {
    return p + (S.s + base * r - p) * 2.0;
  } else return S.s + base * r;
}
