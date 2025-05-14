template <typename T = ll, typename F = ll>
struct SparseTable {
	F f;
	vector<vector<T>> st;
	vector<ll> lookup;

	SparseTable() = default;

	explicit SparseTable(const vector<T> &v, const F &f) : f(f) {
		const ll N = (ll)v.size();
		ll siz = 0;
		ll tmp = N;
		while (tmp != 0) {
			siz++; tmp >>= 1;
		}
		st.assign(siz, vector<T>(N));
		rep(i, v.size()) {
			st[0][i] = v[i];
		}
		reps(i, 1, siz) {
			rep(j, N + 1 - (1 << i)) {
				st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
		lookup.resize(v.size() + 1);
		reps(i, 2, lookup.size()) {
			lookup[i] = lookup[i >> 1] + 1;
		}
	}

	inline T fold(ll l, ll r) const {
		ll b = lookup[r - l];
		return f(st[b][l], st[b][r - (1 << b)]);
	}
};
