struct mint {
	ll x;
	mint(ll y = 0) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
	mint &operator+=(const mint &p) {
		if ((x += p.x) >= mod) x -= mod;
		return *this;
	}
	mint &operator-=(const mint &p) {
		if ((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	mint &operator*=(const mint &p) {
		x = (ll)(1ll * x * p.x % mod);
		return *this;
	}
	mint &operator/=(const mint &p) {
		*this *= p.inv();
		return *this;
	}
	mint operator-() const { return mint(-x); }
	mint operator+(const mint &p) const { return mint(*this) += p; }
	mint operator-(const mint &p) const { return mint(*this) -= p; }
	mint operator*(const mint &p) const { return mint(*this) *= p; }
	mint operator/(const mint &p) const { return mint(*this) /= p; }
	bool operator==(const mint &p) const { return x == p.x; }
	bool operator!=(const mint &p) const { return x != p.x; }
	friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }
	friend istream &operator>>(istream &is, mint &a) {
		ll t; is >> t; a = mint(t); return (is);
	}
	mint inv() const { return pow(mod - 2); }
	mint pow(ll n) const {
		mint ret(1), mul(x);
		while (n > 0) {
			if (n & 1) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ret;
	}
};