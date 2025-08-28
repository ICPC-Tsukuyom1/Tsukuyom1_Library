struct LCTree {
	struct line {
		ll a, b;
		line() : a(0ll), b(numeric_limits<ll>::max() / 4) {}
		line(ll a, ll b) : a(a), b(b) {}
		ll get(ll x) { return a * x + b; }
		inline bool over(line r, ll x) { return get(x) < r.get(x); }
	};
	vl x;
	vec<line> seg;
	ll n;
	LCTree() {}
	LCTree(const vector<ll>&_x) : x(_x) {
		sort(all(x));
		n = 1;
		while (n < sz(x)) n <<= 1;
		while (sz(x) < n) x.push_back(x.back());
		seg = vec<line>(2 * n);
	}
	void update(line L, ll i, ll l, ll r) {
		while (1) {
			ll mid = l + r >> 1;
			bool lov = L.over(seg[i], x[l]);
			bool rov = L.over(seg[i], x[r - 1]);
			if (lov == rov) {
				if (lov) swap(seg[i], L);
				return;
			}
			bool mov = L.over(seg[i], x[mid]);
			if (mov) swap(seg[i], L);
			if (lov != mov) {
				i = (i << 1), r = mid;
			}
			else {
				i = (i << 1) + 1, l = mid;
			}
		}
	}
	void update(line L, unsigned i) {
		ll ub = bit_width(i) - 1;
		ll l = (n >> ub) * (i - (1 << ub));
		ll r = l + (n >> ub);
		update(L, i, l, r);
	}
	void update(ll a, ll b) { update(line(a, b), 1, 0, n); }
	void update_seg(ll l, ll r, ll a, ll b) {
		l = lower_bound(all(x), l) - x.begin() + n, r = lower_bound(all(x), r) - x.begin() + n;
		line L(a, b);
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) update(L, l++);
			if (r & 1) update(L, --r);
		}
	}
	ll query(ll t) {
		ll p = lower_bound(all(x), t) - x.begin();
		p += n;
		ll res = seg[p].get(t);
		while (p > 1) {
			p >>= 1;
			chmin(res, seg[p].get(t));
		}
		return res;
	}
};