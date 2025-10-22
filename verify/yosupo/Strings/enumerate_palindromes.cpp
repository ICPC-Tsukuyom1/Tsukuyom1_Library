//@yosupo enumerate_palindromes

#include "../../../template.cpp"
#include "../../../Strings/Manacher.cpp"
void solve() {
	string s; cin >> s;
	auto m = Manacher(s);
	rep(i, sz(s)) {
		cout << m[1][i] * 2 + 1;
		if (i != sz(s) - 1) cout << ' ' << m[0][i + 1] * 2 << ' ';
	}
	cout << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}