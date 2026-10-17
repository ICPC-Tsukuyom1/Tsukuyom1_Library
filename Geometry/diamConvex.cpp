/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/diamConvex.cpp */
// depends on: convex_hull
pair<Point, Point> diamConvex(Polygon S) {
  Polygon Q = convex_hull(S);
  ll n = sz(Q);
  if (n == 0) return {Point(), Point()};
  ll j = n >= 2;
  pair<ld,pair<Point,Point>> ans({(ld)0,{Q[0],Q[0]}});
  rep(i, j) {
    for (;; j = (j + 1) % n) {
      chmax(ans, {(Q[i] - Q[j]).abs(), {Q[i], Q[j]}});
      if ((Q[(j+1)%n]-Q[j]).cross(Q[i + 1]-Q[i]) > -EPS) break;
    }
  }
  return ans.second;
}