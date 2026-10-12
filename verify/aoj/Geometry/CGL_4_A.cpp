//@aoj CGL_4_A

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/convex_hull.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  Polygon hull = convex_hull(p, false);
  auto first = min_element(all(hull), [](Point a, Point b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
  });
  rotate(hull.begin(), first, hull.end());
  cout << sz(hull) << endl;
  for (Point x : hull) cout << (ll)x.x << ' ' << (ll)x.y << endl;
}
