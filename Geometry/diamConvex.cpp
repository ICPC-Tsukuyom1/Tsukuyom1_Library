// depends on: convex_hull
pair<Point, Point> diamConvex(Polygon S) {
  Polygon Q = convex_hull(S);
  ll n = sz(Q), j = n < 2 ? 0 : 1;
  pair<ld, pair<Point, Point>> ans({(ld)0, {Q[0], Q[0]}});
  rep(i, j) {
    for (;; j = (j + 1) % n) {
      ans = max(ans, {(Q[i] - Q[j]).abs(), {Q[i], Q[j]}});
      if ((Q[(j + 1) % n] - Q[j]).cross(Q[i + 1] - Q[i]) > -EPS) break;
    }
  }
  return ans.second;
}