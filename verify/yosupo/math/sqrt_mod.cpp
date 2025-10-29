//@yosupo sqrt_mod
#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
void solve() {
    ll x, p; cin >> x >> p;
	cout << modsqrt(x, p) << endl;
}
int main() {
    ll T = 1;
    cin >> T;
    while (T--) solve();
}