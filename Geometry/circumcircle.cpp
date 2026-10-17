/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/circumcircle.cpp */
// depends on: Point
// 3 点が同一直線上にある場合は半径 inf の円を返す。
Circle ccCircle(Point &A, Point &B, Point &C) {
  Point b = C - A, c = B - A;
  ld d = b.cross(c);
  if (fabsl(d) < EPS) return Circle(Point(), inf);
  Point ct = A + (b * c.norm() - c * b.norm()).perp() / d / 2;
  ld r = c.abs() * b.abs() * (b - c).abs() / fabsl(d) / 2;
  return Circle(ct, r);
}
