/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/area.cpp */
// depends on: Point
ld Area(Polygon S) {
  ld ans = 0; Point p = S[0];
  rep(i,sz(S)-2) ans+=(S[i+1]-p).cross(S[i+2]-p);
  return ans / 2;
}