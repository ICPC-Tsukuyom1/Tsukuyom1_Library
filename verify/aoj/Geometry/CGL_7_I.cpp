//@aoj CGL_7_I

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/CircCircInter.cpp"
int main() {
  Circle c1, c2;
  cin >> c1.c.x >> c1.c.y >> c1.r;
  cin >> c2.c.x >> c2.c.y >> c2.r;
  cout << fixed << setprecision(10) << (double)fac(c1, c2) << endl;
}
