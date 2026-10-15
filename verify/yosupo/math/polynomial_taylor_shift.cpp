//@yosupo polynomial_taylor_shift
#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"
void solve() {
  ll N, c;
  cin >> N >> c;
  FPS<ll> a(N);
  rep(i, N) cin >> a[i];
  auto b = a.shift(c);
  rep(i, sz(b)) cout << b[i] << " \n"[i == sz(b) - 1];
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}