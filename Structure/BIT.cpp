template <typename T = ll>
struct BIT {
    ll N;
    vector<T>data;

		BIT() = default;
    explicit BIT(ll N_) : N(N_ + 1), data(N + 1, T()) {}
		explicit BIT(vector<T> &v) : BIT((ll)v.size()) { build(v); }
    
    void build(vector<T> &v) {
			rep(i, N) data[i + 1] = v[i];
			reps(i, 1, N + 1) {
				ll j = i + (i & -i);
				if (j <= N) data[j] += data[i];
			}
		}
		
		void apply(ll k, T x) {
			for (++k; k <= N; k += k & -k) data[k] += x;
		}

		T prod(ll r) const {
			T ret = T();
			for (; r > 0; r -= r & -r) ret += data[r];
			return ret;
		}

		T prod(ll l, ll r) const { return prod(r) - prod(l); }

		ll lower_bound(T x) const {
			ll i = 0;
			for (ll k = 1 << (__lg(N) + 1); k > 0; k >>= 1) {
				if (i + k <= N && data[i + k] < x) {
					x -= data[i + k];
					i += k;
				}
			}
			return i;
		}

		ll upper_bound(T x) const {
			ll i = 0;
			for (ll k = 1 << (__lg(N) + 1); k > 0; k >>= 1) {
				if (i + k <= N && data[i + k] <= x) {
					x -= data[i + k];
					i += k;
				}
			}
			return i;
		}
};
