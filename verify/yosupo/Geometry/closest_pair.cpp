//@yosupo closest_pair

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/closest_pair.cpp"

void solve() {
  ll N;
  in >> N;
  Polygon s(N);
  rep(i, N) {
    ll x, y;
    in >> x >> y;
    s[i].x = x;
    s[i].y = y;
  }
  Polygon v = s;
  auto ans = closest(v);
  ll p = -1;
  rep(i, N) {
    if (s[i] == ans.first) { p = i; }
  }
  rep(i, N) {
    if (i == p) continue;
    if (s[i] == ans.second) {
      out << p << ' ' << i << '\n';
      return;
    }
  }
}
int main() {
  ll T = 1;
  in >> T;
  while (T--) solve();
}