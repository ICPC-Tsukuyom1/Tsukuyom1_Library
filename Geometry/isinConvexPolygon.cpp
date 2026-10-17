/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/isinConvexPolygon.cpp */
// depends on: Point
// 反時計回りの凸多角形 S に対し、p が内部なら 2, 辺上なら 1, 外部なら 0 を返す。
// 頂点 S[0] からの扇形を二分探索するので O(log n)。
int isinConvexPolygon(Point p, const Polygon &S) {
  ll n = sz(S);
  if (n == 1) return p == S[0] ? 1 : 0;
  if (n == 2) {
    if (eq((S[1] - S[0]).cross(p - S[0]), (ld)0) &&
        min(S[0].x, S[1].x) <= p.x && p.x <= max(S[0].x, S[1].x) &&
        min(S[0].y, S[1].y) <= p.y && p.y <= max(S[0].y, S[1].y))
      return 1;
    return 0;
  }
  Point o = S[0];
  auto onSeg = [&](Point a, Point b) {
    return eq((b - a).cross(p - a), (ld)0) && min(a.x, b.x) <= p.x &&
           p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
  };
  ld c1 = o.cross(S[1], p), c2 = o.cross(S[n - 1], p);
  if (sign(c1) < 0 || sign(c2) > 0) return 0;
  if (eq(c1, (ld)0)) return onSeg(o, S[1]) ? 1 : 0;
  if (eq(c2, (ld)0)) return onSeg(o, S[n - 1]) ? 1 : 0;
  ll lo = 1, hi = n - 1;
  while (hi - lo > 1) {
    ll mid = (lo + hi) / 2;
    if (sign(o.cross(S[mid], p)) >= 0)
      lo = mid;
    else
      hi = mid;
  }
  ll c3 = sign(S[lo].cross(S[(lo + 1) % n], p));
  if (c3 > 0) return 2;
  if (c3 == 0) return 1;
  return 0;
}
