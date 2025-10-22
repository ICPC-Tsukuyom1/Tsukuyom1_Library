#include "lineInter.cpp"
Polygon polygonCut(Polygon &p, Point s, Point e) {
  Polygon res;
  rep(i, sz(p)) {
    Point cur = p[i], prev = i ? p[i - 1] : p.back();
    bool side = sign(s.cross(e, cur)) < 0;
    if (side != (sign(s.cross(e, prev)) < 0)) {
      res.push_back(lineInter({s, e}, {cur, prev}).second);
    }
    if (side) res.push_back(cur);
  }
  return res;
}