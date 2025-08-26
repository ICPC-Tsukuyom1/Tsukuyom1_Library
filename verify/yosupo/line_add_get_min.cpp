//@yosupo line_add_get_min
#include "../../template.cpp"
#include "../../Structure/LiChaoTree.cpp"
struct query {
	ll t;
	ll a, b;
};
void solve() {
	ll N, Q; cin >> N >> Q;
	vl x;
	v(query) q;
	rep(i, N) {
		ll a, b;
		cin >> a >> b;
		q.emplace_back(0, a, b);
	}
	while (Q--) {
		ll t; cin >> t;
		if (t == 0) {
			ll a, b;
			cin >> a >> b;
			q.emplace_back(t, a, b);
		}
		else {
			ll p; cin >> p;
			q.emplace_back(t, p, 0);
			x.emplace_back(p);
		}
	}
	if (x.empty()) {
		return;
	}
	LCTree lct(x);
	rep(i, sz(q)) {
		if (q[i].t == 0) {
			lct.update(q[i].a, q[i].b);
		}
		else {
			ll ans = lct.query(q[i].a);
			cout << ans << endl;
		}
	}
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) {
		solve();
	}
}