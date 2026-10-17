//@yosupo polynomial_taylor_shift
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"
#include "../../../Math/ntt.cpp"
#include "../../../Math/poly.cpp"

FastIn in;
FastOut out;

using mint = modint<998244353>;

void solve() {
  ll N, c;
  in >> N >> c;
  poly<mint> a(N);
  rep(i, N) {
    ll x;
    in >> x;
    a[i] = mint(x);
  }
  auto b = a.shift(mint(c));
  rep(i, sz(b)) out << b[i].x << " \n"[i == sz(b) - 1];
}
int main() {
  ll T = 1;
  while (T--) solve();
}
