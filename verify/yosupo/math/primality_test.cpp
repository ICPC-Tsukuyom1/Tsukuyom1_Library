//@yosupo primality_test
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/MillerRabin.cpp"

FastIn in;
FastOut out;

int main() {
  ll Q;
  in >> Q;
  while (Q--) {
    ll N;
    in >> N;
    if (isprime(N)) {
      out << "Yes" << '\n';
    } else out << "No" << '\n';
  }
}