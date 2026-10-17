/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/halfPlaneInter.cpp */
// depends on: Point, lineInter
// 各直線の左側の半平面 { p | cross(e - s, p - s) >= 0 } の共通部分を返す。
// 共通部分が空のときは空の多角形を返す（面積 0 の退化ケースでは頂点が重複することがある）。
// 半平面全体が有界になるように直線を与えることを想定している。
Polygon halfPlaneInter(vec<Line> ls) {
  // 偏角でソート
  sort(all(ls), [](const Line &a, const Line &b) {
    Point da = a.e - a.s, db = b.e - b.s;
    auto half = [](Point d) -> int {
      if (d.y < 0) return 0;
      if (d.y == 0 && d.x < 0) return 0;
      return 1;
    };
    int ha = half(da), hb = half(db);
    if (ha != hb) return ha < hb;
    ld c = da.cross(db);
    if (!eq(c, (ld)0)) return c > 0;
    return false;
  });
  // 同方向の平行線を統合し、制約の強い方だけ残す
  vec<Line> L;
  for (Line l : ls) {
    if (!L.empty()) {
      Point d = L.back().e - L.back().s, dl = l.e - l.s;
      if (eq(d.cross(dl), (ld)0) && d.dot(dl) > 0) {
        if (sign(d.cross(l.s - L.back().s)) >= 0) L.back() = l;
        continue;
      }
    }
    L.push_back(l);
  }
  ll n = sz(L);
  if (n < 3) return {};
  auto left = [](const Line &l, const Point &p) {
    return sign((l.e - l.s).cross(p - l.s)) >= 0;
  };
  deque<ll> dq;
  rep(i, n) {
    while (sz(dq) >= 2) {
      auto pr = lineInter(L[dq[sz(dq) - 2]], L[dq.back()]);
      if (pr.first && !left(L[i], pr.second)) dq.pop_back();
      else break;
    }
    while (sz(dq) >= 2) {
      auto pr = lineInter(L[dq[0]], L[dq[1]]);
      if (pr.first && !left(L[i], pr.second)) dq.pop_front();
      else break;
    }
    dq.push_back(i);
  }
  while (sz(dq) >= 3) {
    auto pr = lineInter(L[dq[sz(dq) - 2]], L[dq.back()]);
    if (pr.first && !left(L[dq[0]], pr.second)) dq.pop_back();
    else break;
  }
  while (sz(dq) >= 3) {
    auto pr = lineInter(L[dq[0]], L[dq[1]]);
    if (pr.first && !left(L[dq.back()], pr.second)) dq.pop_front();
    else break;
  }
  Polygon res;
  rep(i, sz(dq)) {
    auto pr = lineInter(L[dq[i]], L[dq[(i + 1) % sz(dq)]]);
    if (!pr.first) return {};
    res.push_back(pr.second);
  }
  return sz(res) < 3 ? Polygon() : res;
}
