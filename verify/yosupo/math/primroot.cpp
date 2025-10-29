#include "../../../template.cpp"
#include "../../../Math/primroot.cpp"

void solve() {
    ll n; cin >> n;
	cout << primroot(n) << endl;
}
int main() {
    ll T = 1;
    cin >> T;
    while (T--) solve();
}