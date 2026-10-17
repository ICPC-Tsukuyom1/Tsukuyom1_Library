/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/isconvex.cpp */
// depends on: Point
// 単純多角形が凸かを判定する。頂点の回転方向がすべて同じ向きで、
// 総回転角がちょうど 2π のときのみ true（自己交差する星形などは false）。
bool isconvex(Polygon S) {
  ll n = sz(S);
  if (n < 3) return false;
  int sgn = 0;
  ld turn = 0;
  rep(i, n) {
    Point a = S[i] - S[(i + n - 1) % n], b = S[(i + 1) % n] - S[i];
    ld cr = a.cross(b);
    int t = sign(cr);
    if (t) {
      if (sgn && sgn != t) return false;
      sgn = t;
    }
    turn += atan2l(cr, a.dot(b));
  }
  if (sgn == 0) return true;  // 全頂点が一直線上（退化）は凸とみなす
  return fabsl(fabsl(turn) - 2 * pi) < 1e-9;
}
