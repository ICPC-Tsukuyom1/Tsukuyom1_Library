// depends on: Point
ld segDist(Point s, Point e, Point p) {
  if (s==e) return(p-s).abs();
  auto d=(e-s).norm(),t=min(d,max(ld(0),(p-s).dot(e-s)));
  return ((p-s)*d-(e-s)*t).abs()/d;
}