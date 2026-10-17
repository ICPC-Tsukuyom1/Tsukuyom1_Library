//@yosupo sum_of_floor_of_linear

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/floorsum.cpp"

FastIn in;
FastOut out;

void solve() {
  ll n, m, a, b;
  in >> n >> m >> a >> b;
  out << floorsum(n, a, b, m) << '\n';
}
int main() {
  ll T = 1;
  in >> T;
  while (T--) solve();
}