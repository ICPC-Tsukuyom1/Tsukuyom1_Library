//@yosupo pow_of_formal_power_series
#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"

void solve() {
  ll N, M;
  cin >> N >> M;
  FPS<ll> a(N);
  rep(i, N) cin >> a[i];
  auto ans = a.pow(M);
  rep(i, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}