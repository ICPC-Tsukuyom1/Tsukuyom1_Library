//@yosupo pow_of_formal_power_series
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"

FastIn in;
FastOut out;

void solve() {
  ll N, M;
  in >> N >> M;
  FPS<ll> a(N);
  rep(i, N) in >> a[i];
  auto ans = a.pow(M);
  rep(i, sz(ans)) out << ans[i] << " \n"[i == sz(ans) - 1];
}
int main() {
  ll T = 1;
  while (T--) solve();
}