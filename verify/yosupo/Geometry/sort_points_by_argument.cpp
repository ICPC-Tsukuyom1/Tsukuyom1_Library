//@yosupo sort_points_by_argument

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/argSort.cpp"
int main() {
  ll n;
  in >> n;
  Polygon p(n);
  rep(i, n) {
    ll x, y;
    in >> x >> y;
    p[i].x = x;
    p[i].y = y;
  }
  stable_sort(all(p), argCmp);
  rep(i, n) out << (ll)p[i].x << ' ' << (ll)p[i].y << '\n';
}
