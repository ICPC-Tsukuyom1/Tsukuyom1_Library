//@yosupo many_aplusb

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

int main() {
  ll t;
  in >> t;
  while (t--) {
    ll a, b;
    in >> a >> b;
    out << a + b << '\n';
  }
}
