/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/ssDist.cpp */
// depends on: Point, segDistance, segInter

ld ssDist(Segment S1, Segment S2) {
  if (sz(segInter(S1, S2))) return 0.0;
  return min(min(segDist(S1.s, S1.e, S2.s), segDist(S1.s, S1.e, S2.e)),
             min(segDist(S2.s, S2.e, S1.s), segDist(S2.s, S2.e, S1.e)));
}