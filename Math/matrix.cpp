template <typename T>
class Matrix {
	typedef Matrix M;
public:
	vv<T> a;
	ll n, m;
	Matrix(ll n, ll m): n(n), m(m), a(n, vec<T>(m)) {}
	Matrix(ll n = 0): M(n, n) {}
	vec<T>& operator[](ll k) { return a[k]; }
	const vec<T>& operator[](ll k) const { return a[k]; }
	static M I(ll n) {
		M mat(n);
		rep(i, n) mat[i][i] = 1;
		return mat;
	}
	M& operator+=(const M& b) {
		rep(i, n) rep(j, m) (*this)[i][j] += b[i][j];
		return *this;
	}
	M& operator-=(const M& b) {
		rep(i, n) rep(j, m) (*this)[i][j] -= b[i][j];
		return *this;
	}
	M& operator*=(const M& b) {
		ll l = b.m;
		vv<T> c(n, vec<T>(l));
		rep(i, n) rep(j, m) rep(k, l) c[i][k] += (*this)[i][j] * b[j][k];
		a.swap(c);
		return *this;
	}
	M& operator^=(ll k) {
		M b = M::I(n);
		while (k) {
			if (k & 1) b *= *this;
			*this *= *this;
			k >>= 1;
		}
		a.swap(b.a);
		return *this;
	}
	bool operator==(const M& b) const {
		if (n != b.n || m != b.m) return false;
		rep(i, n) rep(j, m) if ((*this)[i][j] != b[i][j]) return false;
		return true;
	}
	M operator+(const M& b) const { return M(*this) += b; }
	M operator-(const M& b) const { return M(*this) -= b; }
	M operator*(const M& b) const { return M(*this) *= b; }
	M operator^(const ll& k) const { return M(*this) ^= k; }

	T det() {
		M B(*this);
		assert(n == m);
		T ret = 1;
		rep(i, n) {
			ll idx = -1;
			reps(j, i, n) if(B[j][i] != 0) idx = j;
			if (idx == -1) return 0;
			if (i != idx) { ret *= -1; swap(B[i], B[idx]); }
			ret *= B[i][i];
			T vv = B[i][i];
			rep(j, n) B[i][j] /= vv;
			reps(j, i + 1, n) {
				T a = B[j][i];
				rep(k, n) B[j][k] -= B[i][k] * a;
			}
		}
		return ret;
	}
};