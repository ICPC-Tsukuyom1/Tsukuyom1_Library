//@yosupo sqrt_of_formal_power_series
#include "../../../template.cpp"
#include "../../../Math/fps.cpp"
void solve() {
	ll N; cin >> N;
	FPS<ll> a(N); cin >> a;
	auto ans = a.sqrt();
	if (ans.empty()) {
		cout << -1 << endl;
	}
	else cout << ans << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}