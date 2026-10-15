//@yosupo minimum_enclosing_circle

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/circumcircle.cpp"
#include "../../../Geometry/minEncloseCirc.cpp"

int main() {
  ll n;
  cin >> n;
  Polygon s(n);
  rep(i, n) cin >> s[i].x >> s[i].y;
  Circle ans = mec(s);
  rep(i, n) { cout << eq((ans.c - s[i]).abs(), ans.r); }
  cout << endl;
}