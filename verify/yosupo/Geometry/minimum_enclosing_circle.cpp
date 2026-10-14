//@yosupo minimum_enclosing_circle

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/circumcircle.cpp"
#include "../../../Geometry/minEncloseCirc.cpp"

int main() {
  ll n;
  in >> n;
  Polygon s(n);
  rep(i, n) {
    ll x, y;
    in >> x >> y;
    s[i].x = x;
    s[i].y = y;
  }
  Circle ans = mec(s);
  rep(i, n) { out << eq((ans.c - s[i]).abs(), ans.r); }
  out << '\n';
}