//@aoj CGL_2_D

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/segDistance.cpp"
#include "../../../Geometry/onSegment.cpp"
#include "../../../Geometry/segInter.cpp"
#include "../../../Geometry/ssDist.cpp"
int main() {
  ll q;
  cin >> q;
  while (q--) {
    Segment a, b;
    cin >> a.s.x >> a.s.y >> a.e.x >> a.e.y;
    cin >> b.s.x >> b.s.y >> b.e.x >> b.e.y;
    cout << fixed << setprecision(10) << (double)ssDist(a, b) << endl;
  }
}
