//@aoj CGL_7_C

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/circumcircle.cpp"
int main() {
  Point a, b, c;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
  Circle cc = ccCircle(a, b, c);
  cout << fixed << setprecision(10) << (double)cc.c.x << ' ' << (double)cc.c.y << ' '
       << (double)cc.r << endl;
}
