//@yosupo division_of_big_integers

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
    auto [q, r] = BigInt(a).divmod(BigInt(b));
    out << q.to_string() << ' ' << r.to_string() << '\n';
  }
}
