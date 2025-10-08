//@yosupo general_matching

#include "../../../template.cpp"
#include "../../../Graph/maxMatching.cpp"
void solve() {
	ll n, m; cin >> n >> m;
	vv<ll> g(n);
	rep(i, m) {
		ll u, v; cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	maxMatch a(g);
	auto ans = a.max_match();
	cout << sz(ans) << endl;
	rep(i, sz(ans)) {
		cout << ans[i].first << ' ' << ans[i].second << endl;
	}
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}