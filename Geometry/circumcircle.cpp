// depends on: Point
Circle ccCicle(Point &A, Point &B, Point &C) {
  Point b = C - A, c = B - A;
  Point center = A + (b * c.norm() - c * b.norm()).perp() / b.cross(c) / 2;
  ld radius = (B - A).abs() * (C - B).abs() * (A - C).abs() /
              fabs((B - A).cross(C - A)) / 2;
  return Circle(center, radius);
}