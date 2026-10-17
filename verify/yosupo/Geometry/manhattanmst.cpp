//@yosupo manhattanmst

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Structure/unionfind.cpp"
#include "../../../Geometry/manhattanMST.cpp"
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
  vec<array<ll, 3>> es = manhattanMST(p);
  ll sum = 0;
  for (auto &e : es) sum += e[0];
  out << sum << '\n';
  for (auto &e : es) out << e[1] << ' ' << e[2] << '\n';
}
