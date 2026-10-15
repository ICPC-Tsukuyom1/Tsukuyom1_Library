/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/aoj/Geometry/CGL_1_C.cpp */
//@aoj CGL_1_C

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/ccw.cpp"
int main() {
  Point a, b;
  cin >> a.x >> a.y >> b.x >> b.y;
  ll q;
  cin >> q;
  while (q--) {
    Point p;
    cin >> p.x >> p.y;
    int result = ccw(a, b, p);
    if (result == COUNTER_CLOCKWISE)
      cout << "COUNTER_CLOCKWISE" << endl;
    else if (result == CLOCKWISE)
      cout << "CLOCKWISE" << endl;
    else if (result == ONLINE_BACK)
      cout << "ONLINE_BACK" << endl;
    else if (result == ONLINE_FRONT)
      cout << "ONLINE_FRONT" << endl;
    else
      cout << "ON_SEGMENT" << endl;
  }
}
