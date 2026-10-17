//@aoj CGL_4_C

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/area.cpp"
#include "../../../Geometry/lineInter.cpp"
#include "../../../Geometry/Polygon_cut.cpp"
int main() {
  ll n;
  cin >> n;
  Polygon p(n);
  rep(i, n) cin >> p[i].x >> p[i].y;
  ll q;
  cin >> q;
  while (q--) {
    Point s, e;
    cin >> s.x >> s.y >> e.x >> e.y;
    Polygon cut = polygonCut(p, e, s);
    ld area = sz(cut) < 3 ? 0 : fabs(Area(cut));
    cout << fixed << setprecision(8) << (double)area << endl;
  }
}
