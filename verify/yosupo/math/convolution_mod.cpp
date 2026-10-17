//@yosupo convolution_mod

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"
#include "../../../Math/ntt.cpp"
#include "../../../Math/poly.cpp"

FastIn in;
FastOut out;

using mint = modint<998244353>;

int main() {
  ll N, M;
  in >> N >> M;
  poly<mint> a(N), b(M);
  rep(i, N) {
    ll x;
    in >> x;
    a[i] = mint(x);
  }
  rep(i, M) {
    ll x;
    in >> x;
    b[i] = mint(x);
  }
  poly<mint> c = a * b;
  rep(i, sz(c)) out << c[i].x << " \n"[i == sz(c) - 1];
}
