//@yosupo log_of_formal_power_series
#include "../../../template.cpp"
#include "../../../Math/fps.cpp"

void solve() {
	ll N; cin >> N;
	FPS<ll> a(N); cin >> a;
	cout << a.log() << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}