/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/closest_pair.cpp */
// depends on: Point
pair<Point, Point> closest(Polygon &v) {
  set<Point> s;
  sort(all(v), [](Point a, Point b) { return a.y < b.y; });
  pair<ld, pair<Point, Point>> ans = {LDBL_MAX, {Point(), Point()}};
  ll j = 0;
  for (Point p : v) {
    Point d{ans.first, 0};
    while (j < sz(v) && v[j].y <= p.y - d.x) s.erase(v[j++]);
    auto lo = s.lower_bound(p - d), hi = s.upper_bound(p + d);
    for (; lo != hi; lo = ++lo) chmin(ans, {(*lo - p).abs(), {*lo, p}});
    s.insert(p);
  }
  return ans.second;
}
