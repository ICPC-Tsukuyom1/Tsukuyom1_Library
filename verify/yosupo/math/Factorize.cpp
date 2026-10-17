//@yosupo factorize

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/MillerRabin.cpp"
#include "../../../Math/FastFactorize.cpp"

FastIn in;
FastOut out;

int main() {
  ll Q;
  in >> Q;
  while (Q--) {
    ll N;
    in >> N;
    auto f = fac(N);
    out << f.size();
    sort(all(f));
    for (ll p : f) { out << ' ' << p; }
    out << '\n';
  }
}
