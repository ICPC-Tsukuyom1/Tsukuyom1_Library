/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/aoj/Geometry/CGL_3_C.cpp */
//@aoj CGL_3_C

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/isinpolygon.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  ll q;
  cin >> q;
  while (q--) {
    Point x;
    cin >> x.x >> x.y;
    cout << isinPolygon(x, p) << endl;
  }
}
