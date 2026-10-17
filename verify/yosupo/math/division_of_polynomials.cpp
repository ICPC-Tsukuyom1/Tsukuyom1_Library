//@yosupo division_of_polynomials
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"
#include "../../../Math/ntt.cpp"
#include "../../../Math/poly.cpp"

FastIn in;
FastOut out;

using mint = modint<998244353>;

void solve() {
  ll N, M;
  in >> N >> M;
  poly<mint> a(N);
  rep(i, N) {
    ll x;
    in >> x;
    a[i] = mint(x);
  }
  poly<mint> b(M);
  rep(i, M) {
    ll x;
    in >> x;
    b[i] = mint(x);
  }
  auto ans = a.div_mod(b);
  out << sz(ans.first) << ' ' << sz(ans.second) << '\n';
  rep(i, sz(ans.first)) out << ans.first[i].x << " \n"[i == sz(ans.first) - 1];
  rep(i, sz(ans.second)) out << ans.second[i].x << " \n"[i == sz(ans.second) - 1];
}
int main() {
  ll T = 1;
  while (T--) solve();
}
