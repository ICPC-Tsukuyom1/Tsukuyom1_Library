//@yosupo bitwise_and_convolution

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#include "../../../Math/bitwise_or_convolution.cpp"

FastIn in;
FastOut out;

int main() {
  int n;
  in >> n;
  vec<mint> a(1 << n), b(1 << n);
  rep(i, 1 << n) {
    ll temp;
    in >> temp;
    a[i] = mint(temp);
  }
  rep(i, 1 << n) {
    ll temp;
    in >> temp;
    b[i] = mint(temp);
  }
  reverse(all(a));
  reverse(all(b));
  auto c = or_conv(a, b);
  reverse(all(c));
  rep(i, 1 << n) out << c[i].x << " \n"[i == (1 << n) - 1];
}