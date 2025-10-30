//@yosupo division_of_polynomials
#include "../../../template.cpp"
#include "../../../Math/fps.cpp"
void solve() {
	ll N, M; cin >> N >> M;
	FPS<ll> a(N); 
    rep(i, N) cin >> a[i];
	FPS<ll> b(M); 
    rep(i, M) cin >> b[i];
	auto ans = a.div_mod(b);
	cout << sz(ans.first) << ' ' << sz(ans.second) << endl;
    rep(i, sz(ans.first)) cout << ans.first[i] << " \n"[i == sz(ans.first) - 1];
    rep(i, sz(ans.second)) cout << ans.second[i] << " \n"[i == sz(ans.second) - 1];
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}