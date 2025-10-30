//@yosupo polynomial_taylor_shift
#include "../../../template.cpp"
#include "../../../Math/fps.cpp"
void solve() {
	ll N, c; cin >> N >> c;
	FPS<ll> a(N); cin >> a;
	auto b = a.shift(c);
	cout << b << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}