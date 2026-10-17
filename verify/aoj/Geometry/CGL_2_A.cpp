//@aoj CGL_2_A

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/isParallel.cpp"
int main() {
  ll q;
  cin >> q;
  while (q--) {
    Point p0, p1, p2, p3;
    cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    Line l1{p0, p1}, l2{p2, p3};
    if (isParallel(l1, l2))
      cout << 2 << endl;
    else if (isOrthogonal(l1, l2))
      cout << 1 << endl;
    else
      cout << 0 << endl;
  }
}
