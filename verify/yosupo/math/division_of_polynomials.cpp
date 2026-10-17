//@yosupo division_of_polynomials
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
  FPS<ll> b(M);
  rep(i, M) in >> b[i];
  auto ans = a.div_mod(b);
  out << sz(ans.first) << ' ' << sz(ans.second) << '\n';
  rep(i, sz(ans.first)) out << ans.first[i] << " \n"[i == sz(ans.first) - 1];
  rep(i, sz(ans.second)) out << ans.second[i] << " \n"[i == sz(ans.second) - 1];
}
int main() {
  ll T = 1;
  while (T--) solve();
}