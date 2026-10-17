//@yosupo sqrt_mod
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"

FastIn in;
FastOut out;

void solve() {
  ll x, p;
  in >> x >> p;
  out << modsqrt(x, p) << '\n';
}
int main() {
  ll T = 1;
  in >> T;
  while (T--) solve();
}