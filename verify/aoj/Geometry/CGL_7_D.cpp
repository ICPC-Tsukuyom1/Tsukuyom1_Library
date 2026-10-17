//@aoj CGL_7_D

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/projection.cpp"
#include "../../../Geometry/clInter.cpp"
int main() {
  Circle c;
  cin >> c.c.x >> c.c.y >> c.r;
  ll q;
  cin >> q;
  while (q--) {
    Line l;
    cin >> l.s.x >> l.s.y >> l.e.x >> l.e.y;
    auto ans = clInter(c, l);
    cout << fixed << setprecision(8) << (double)ans.first.x << ' '
         << (double)ans.first.y << ' ' << (double)ans.second.x << ' '
         << (double)ans.second.y << endl;
  }
}
