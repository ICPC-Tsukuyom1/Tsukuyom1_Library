/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/isParallel.cpp */
// depends on: Point
// 2 直線が平行か
bool isParallel(Line l1, Line l2) {
  return eq((l1.e - l1.s).cross(l2.e - l2.s), (ld)0);
}
// 2 直線が垂直か
bool isOrthogonal(Line l1, Line l2) {
  return eq((l1.e - l1.s).dot(l2.e - l2.s), (ld)0);
}
