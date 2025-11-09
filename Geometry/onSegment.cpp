// depends on: Point
bool onSegment(Segment S, Point p) {
  return eq(p.cross(S.s, S.e), (ld)0) && (S.s - p).dot(S.e - p) <= EPS;
}