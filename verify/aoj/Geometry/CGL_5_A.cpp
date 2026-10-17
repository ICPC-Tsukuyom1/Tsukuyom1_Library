//@aoj CGL_5_A

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/closest_pair.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  auto ans = closest(p);
  cout << fixed << setprecision(10) << (double)(ans.first - ans.second).abs() << endl;
}
