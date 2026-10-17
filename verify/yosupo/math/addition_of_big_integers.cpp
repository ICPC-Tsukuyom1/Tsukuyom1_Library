//@yosupo addition_of_big_integers

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/BigInt.cpp"

FastIn in;
FastOut out;

int main() {
  ll T;
  in >> T;
  while (T--) {
    string a, b;
    in >> a >> b;
    out << (BigInt(a) + BigInt(b)).to_string() << '\n';
  }
}
