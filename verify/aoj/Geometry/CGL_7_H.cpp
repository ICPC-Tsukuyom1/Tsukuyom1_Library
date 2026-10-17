//@aoj CGL_7_H

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/CircPolyInter.cpp"
int main() {
  ll n;
  ld r;
  cin >> n >> r;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  cout << fixed << setprecision(10) << (double)fabs(fac(Circle(Point(0, 0), r), p))
       << endl;
}
