//@aoj CGL_7_B

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/area.cpp"
#include "../../../Geometry/trincircle.cpp"
int main() {
  Polygon p(3);
  rep(i, 3) cin >> p[i].x >> p[i].y;
  Circle c = trinCircle(p);
  cout << fixed << setprecision(10) << (double)c.c.x << ' ' << (double)c.c.y << ' '
       << (double)c.r << endl;
}
