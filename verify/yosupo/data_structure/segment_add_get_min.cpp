//@yosupo segment_add_get_min
#include "../../../template.cpp"
#include "../../../Structure/LiChaoTree.cpp"
struct query {
	ll t;
	ll l, r, a, b;
};
void solve() {
	ll N, Q; cin >> N >> Q;
	vl x;
	ll Max = 1000000007;
	const ll INF = numeric_limits<ll>::max() / 4;
	vec<query> q;
	rep(i, N) {
		ll l, r, a, b;
		cin >> l >> r >> a >> b;
		q.emplace_back(0, l, r, a, b);
	}
	while (Q--) {
		ll t; cin >> t;
		if (t == 0) {
			ll l, r, a, b;
			cin >> l >> r >> a >> b;
			q.emplace_back(t, l, r, a, b);
		}
		else {
			ll p; cin >> p;
			q.emplace_back(t, p, 0, 0, 0);
			x.emplace_back(p);
		}
	}
	if (x.empty()) {
		return;
	}
	LCTree lct(x);
	rep(i, sz(q)) {
		if (q[i].t == 0) {
			lct.update_seg(q[i].l, q[i].r, q[i].a, q[i].b);
		}
		else {
			ll ans = lct.query(q[i].l);
			if (ans == INF) {
				cout << "INFINITY" << endl;
			}
			else cout << ans << endl;
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