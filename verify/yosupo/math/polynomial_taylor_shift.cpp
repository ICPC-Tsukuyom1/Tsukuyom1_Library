//@yosupo polynomial_taylor_shift
#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"

FastIn in;
FastOut out;

void solve() {
  ll N, c;
  in >> N >> c;
  FPS<ll> a(N);
  rep(i, N) in >> a[i];
  auto b = a.shift(c);
  rep(i, sz(b)) out << b[i] << " \n"[i == sz(b) - 1];
}
int main() {
  ll T = 1;
  while (T--) solve();
}