//@aoj CGL_3_B

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/isconvex.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  cout << (isconvex(p) ? 1 : 0) << endl;
}
