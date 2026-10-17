//@yosupo pow_of_formal_power_series
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/ntt.cpp"
#include "../../../Math/poly.cpp"
#include "../../../Math/fps.cpp"

FastIn in;
FastOut out;

using mint = modint<998244353>;

void solve() {
  ll N, M;
  in >> N >> M;
  fps<mint> a(N);
  rep(i, N) {
    ll x;
    in >> x;
    a[i] = mint(x);
  }
  auto ans = a.pow(M);
  rep(i, sz(ans)) out << ans[i].x << " \n"[i == sz(ans) - 1];
}
int main() {
  ll T = 1;
  while (T--) solve();
}
