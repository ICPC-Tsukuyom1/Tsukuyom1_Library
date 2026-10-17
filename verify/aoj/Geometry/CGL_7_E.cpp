//@aoj CGL_7_E

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/commonTangents.cpp"
#include "../../../Geometry/ccInter.cpp"
int main() {
  Circle c1, c2;
  cin >> c1.c.x >> c1.c.y >> c1.r;
  cin >> c2.c.x >> c2.c.y >> c2.r;
  auto ans = ccInter(c1, c2);
  cout << fixed << setprecision(8) << (double)ans.first.x << ' '
       << (double)ans.first.y << ' ' << (double)ans.second.x << ' '
       << (double)ans.second.y << endl;
}
