//@yosupo all_furthest_neighbors

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/furthestNeighbors.cpp"
int main() {
  ll T;
  in >> T;
  while (T--) {
    ll n;
    in >> n;
    Polygon p(n);
    rep(i, n) {
      ll x, y;
      in >> x >> y;
      p[i].x = x;
      p[i].y = y;
    }
    vec<ll> f = furthestNeighbors(p);
    rep(i, n) {
      if (i) out << ' ';
      out << f[i];
    }
    out << '\n';
  }
}
