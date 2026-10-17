/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/LineDistance.cpp */
// depends on: Point
// Line{s, e}, Point p; d=lineDist(s,e,p)
// 直線 s->e から p までの符号付き距離を返す（直線の左側が正）。
ld lineDist(Point s, Point e, Point p) {
  return (e-s).cross(p-s)/(e-s).abs();
}
