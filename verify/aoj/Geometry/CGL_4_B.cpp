//@aoj CGL_4_B

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/convex_hull.cpp"
#include "../../../Geometry/diamConvex.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  auto d = diamConvex(p);
  cout << fixed << setprecision(10) << (double)(d.first - d.second).abs() << endl;
}
