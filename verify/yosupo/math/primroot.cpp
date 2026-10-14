//@yosupo primitive_root

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/MillerRabin.cpp"
#include "../../../Math/FastFactorize.cpp"
#include "../../../Math/primroot.cpp"

FastIn in;
FastOut out;

void solve() {
  ll n;
  in >> n;
  out << primroot(n) << '\n';
}
int main() {
  ll T = 1;
  in >> T;
  while (T--) solve();
}