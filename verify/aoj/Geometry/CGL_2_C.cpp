//@aoj CGL_2_C

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/lineInter.cpp"
int main() {
  ll q;
  cin >> q;
  while (q--) {
    Line a, b;
    cin >> a.s.x >> a.s.y >> a.e.x >> a.e.y;
    cin >> b.s.x >> b.s.y >> b.e.x >> b.e.y;
    Point p = lineInter(a, b).second;
    cout << fixed << setprecision(10) << (double)p.x << ' ' << (double)p.y << endl;
  }
}
