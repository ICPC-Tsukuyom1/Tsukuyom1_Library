//@yosupo furthest_pair

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/convex_hull.cpp"
#include "../../../Geometry/diamConvex.cpp"
void solve() {
  ll n;
  in >> n;
  Polygon g(n);
  rep(i, n) {
    ll x, y;
    in >> x >> y;
    g[i].x = x;
    g[i].y = y;
  }
  auto res = diamConvex(g);
  ll l, r;
  rep(i, n) if (res.first == g[i]) {
    l = i;
    break;
  }
  rep(i, n) if (res.second == g[i] && l != i) {
    r = i;
    break;
  }
  out << l << ' ' << r << '\n';
}
int main() {
  ll T = 1;
  in >> T;
  while (T--) solve();
}