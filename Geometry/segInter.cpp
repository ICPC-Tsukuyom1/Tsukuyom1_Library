// depends on: Point, onSegment
vec<Point> segInter(Point a, Point b, Point c, Point d) {
  ld oa=c.cross(d,a),ob=c.cross(d,b)
  ld oc=a.cross(b,c),od=a.cross(b,d);
  if (sign(oa)*sign(ob)<0 && sign(oc)*sign(od)<0)
    return {(a*ob-b*oa)/(ob-oa)};
  set<Point>s;
  if (onSegment({c, d}, a)) s.insert(a);
  if (onSegment({c, d}, b)) s.insert(b);
  if (onSegment({a, b}, c)) s.insert(c);
  if (onSegment({a, b}, d)) s.insert(d);
  return {all(s)};
}
vec<Point> segInter(Segment a, Segment b) {
  return segInter(a.s, a.e, b.s, b.e);
}
// check sz(segInter) > 0