//@yosupo division_of_polynomials
#include "../../../template.cpp"
#include "../../../Math/fps.cpp"
void solve() {
	ll N, M; cin >> N >> M;
	FPS<ll> a(N); cin >> a;
	FPS<ll> b(M); cin >> b;
	auto ans = a.div_mod(b);
	cout << sz(ans.first) << ' ' << sz(ans.second) << endl;
	cout << ans.first << ans.second << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}