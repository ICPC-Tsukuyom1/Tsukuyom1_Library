// depends on: Point
pair<Point, Point> circTangents(Circle c, Point p) {
  ld theta = acosl(c.r / (p - c.c).abs());
  Point i = c.c + (p - c.c).unit() * c.r;
  pair<Point, Point> ret =
      make_pair(i.rotate(theta, c.c), i.rotate(-theta, c.c));
  if (!(ret.first < ret.second)) swap(ret.first, ret.second);
  return ret;
}