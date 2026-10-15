//@yosupo exp_of_formal_power_series
#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"

void solve() {
  ll N;
  cin >> N;
  FPS<ll> a(N);
  rep(i, N) cin >> a[i];
  auto ans = a.exp();
  rep(i, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}