//@yosupo static_convex_hull

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/convex_hull.cpp"
int main() {
  ll T;
  in >> T;
  while (T--) {
    ll N;
    in >> N;
    Polygon S(N);
    rep(i, N) {
      ll x, y;
      in >> x >> y;
      S[i].x = x;
      S[i].y = y;
    }
    Polygon ans = convex_hull(S);
    out << sz(ans) << '\n';
    rep(i, sz(ans)) { out << (ll)ans[i].x << ' ' << (ll)ans[i].y << '\n'; }
  }
}