//@yosupo many_aplusb

#include "../../../template.cpp"
#include "../../fastio.hpp"

int main() {
  FastIn in;
  FastOut out;
  ll t;
  in >> t;
  while (t--) {
    ll a, b;
    in >> a >> b;
    out << a + b << '\n';
  }
}
