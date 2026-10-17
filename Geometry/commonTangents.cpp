/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/commonTangents.cpp */
// depends on: Point
// 2 円の共通接線を返す。各接線の s が c1 の接点、e が c2 の接点。
// 2 円が接する場合、縮退した接線は接点 1 点（s == e）として 1 本だけ返す。同心円なら空。
vec<Line> commonTangents(Circle c1, Circle c2) {
  Point a = c1.c, b = c2.c;
  ld r1 = c1.r, r2 = c2.r;
  ld d = (b - a).abs();
  vec<Line> ans;
  if (d < EPS) return ans;
  ld ang = (b - a).angle();
  auto add = [&](ld t, bool inner) {
    Point u(cosl(t), sinl(t));
    if (inner) ans.push_back(Line(a + u * r1, b - u * r2));
    else ans.push_back(Line(a + u * r1, b + u * r2));
  };
  // 外公接線（接点の半径が同方向）
  if (fabsl(r1 - r2) <= d + EPS) {
    ld phi = acosl(min((ld)1, max((ld)-1, (r1 - r2) / d)));
    add(ang + phi, false);
    if (d > fabsl(r1 - r2) + EPS) add(ang - phi, false);
  }
  // 内公接線（接点の半径が逆方向）
  if (r1 + r2 <= d + EPS) {
    ld phi = acosl(min((ld)1, max((ld)-1, (r1 + r2) / d)));
    add(ang + phi, true);
    if (d > r1 + r2 + EPS) add(ang - phi, true);
  }
  return ans;
}
