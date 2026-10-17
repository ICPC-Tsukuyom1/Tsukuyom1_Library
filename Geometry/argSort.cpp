/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/argSort.cpp */
// depends on: Point
// 偏角ソート用の比較関数。
// 半直線 x <= 0, y = 0 を始点に反時計回りに並べる。
// 同じ偏角の点同士は等価（stable_sort なら入力順が保たれる）。
bool argCmp(const Point &a, const Point &b) {
  auto pos = [](const Point &p) -> int {
    if (p.y < 0) return -1;
    if (p.y == 0 && 0 <= p.x) return 0;
    return 1;
  };
  int pa = pos(a), pb = pos(b);
  if (pa != pb) return pa < pb;
  return a.cross(b) > 0;
}
void argSort(Polygon &p) { stable_sort(all(p), argCmp); }
