#include "Point.cpp"
#include "segDistance.cpp"
#include "segInter.cpp"

ld ssDist(Segment S1, Segment S2) {
  if (sz(segInter(S1, S2))) return 0.0;
  return min(min(segDist(S1, S2.s), segDist(S1, S2.e)),
             min(segDist(S2, S1.s), segDist(S2, S1.e)));
}