/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/aoj/Geometry/CGL_3_A.cpp */
//@aoj CGL_3_A

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/area.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  cout << fixed << setprecision(10) << (double)fabs(Area(p)) << endl;
}
