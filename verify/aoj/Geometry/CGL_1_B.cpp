//@aoj CGL_1_B

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/projection.cpp"
int main() {
  Point a, b;
  cin >> a.x >> a.y >> b.x >> b.y;
  Segment line{a, b};
  ll q;
  cin >> q;
  while (q--) {
    Point p;
    cin >> p.x >> p.y;
    Point ans = Projection(line, p, true);
    cout << fixed << setprecision(10) << (double)ans.x << ' ' << (double)ans.y << endl;
  }
}
