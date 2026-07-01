//@yosupo division_of_polynomials
#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"
void solve() {
  ll N, M;
  cin >> N >> M;
  FPS<ll> a(N);
  rep(i, N) cin >> a[i];
  FPS<ll> b(M);
  rep(i, M) cin >> b[i];
  auto ans = a.div_mod(b);
  cout << sz(ans[0]) << ' ' << sz(ans[1]) << endl;
  rep(i, sz(ans[0])) cout << ans[0][i] << " \n"[i == sz(ans[0]) - 1];
  rep(i, sz(ans[1])) cout << ans[1][i]
                              << " \n"[i == sz(ans[1]) - 1];
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}