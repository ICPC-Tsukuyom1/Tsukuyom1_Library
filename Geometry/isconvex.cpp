// depends on: Point, ccw
bool isconvex(Polygon S) {
  ll n = sz(S);
  bool c = true;
  rep(i, n)
    c &= (ccw(S[(i+n-1) % n],S[i],S[(i+1) % n]) != -1);
  return c;
}