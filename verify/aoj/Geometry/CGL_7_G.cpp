//@aoj CGL_7_G

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/commonTangents.cpp"
int main() {
  Circle c1, c2;
  cin >> c1.c.x >> c1.c.y >> c1.r;
  cin >> c2.c.x >> c2.c.y >> c2.r;
  vec<Point> pts;
  for (auto &l : commonTangents(c1, c2)) pts.push_back(l.s);
  sort(all(pts), [](Point a, Point b) {
    if (fabs(a.x - b.x) > EPS) return a.x < b.x;
    return a.y < b.y;
  });
  for (auto &p : pts)
    cout << fixed << setprecision(10) << (double)p.x << ' ' << (double)p.y << endl;
}
