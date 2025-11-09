// depends on: Point
ld Area(Polygon S) {
  ld ans = 0;
  rep(i, sz(S) - 2) { ans += (S[i + 1] - S[0]).cross(S[i + 2] - S[0]) * 0.5; }
  return ans;
}