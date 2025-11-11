// depends on: Point
Circle ccCircle(Point &A, Point &B, Point &C) {
  Point b=C-A, c=B-A;
  Point ct = A+(b*c.norm()-c*b.norm()).perp()/b.cross(c)/2;
  ld r=c.abs()*(C-B).abs()*(A-C).abs()/fabs(c.cross(C-A))/2;
  return Circle(ct, r);
}