/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/LineDistance.cpp */
// depends on: Point
// Line{s, e}, Point p; d=lineDist(s,e,p)
ld lineDist(Point s, Point e, Point p) {
  return (e-s).cross(p-s)/(e-s).abs();
}