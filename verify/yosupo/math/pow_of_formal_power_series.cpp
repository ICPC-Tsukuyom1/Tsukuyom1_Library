//@yosupo pow_of_formal_power_series
#include "../../../template.cpp"
#include "../../../Math/fps.cpp"

void solve() {
	ll N, M; cin >> N >> M;
	FPS<ll> a(N); cin >> a;
	cout << a.pow(M) << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}