//@aoj CGL_7_F

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/circleTangents.cpp"
int main() {
  Point p;
  cin >> p.x >> p.y;
  Circle c;
  cin >> c.c.x >> c.c.y >> c.r;
  auto ans = circTangents(c, p);
  cout << fixed << setprecision(10) << (double)ans.first.x << ' '
       << (double)ans.first.y << endl;
  cout << fixed << setprecision(10) << (double)ans.second.x << ' '
       << (double)ans.second.y << endl;
}
