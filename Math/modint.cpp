// "mod" should be prime
template <int MOD> 
struct modint {
    static_assert(MOD == 0 || MOD >= 2);
    using mint = modint<MOD>;

private:
    inline static int run_mod = 0;

public:

    static int mod() {
        if constexpr (MOD != 0) {
            return MOD;
        } else {
            assert(run_mod >= 2);
            return run_mod;
        }
    }

    static void set_mod(int p) {
        static_assert(MOD == 0);
        assert(run_mod == 0);
        assert(p >= 2);
        run_mod = p;
    }

    long long x;

    modint(long long y = 0) : x(y % mod()) {
        if (x < 0) x += mod();
    }

    mint &operator+=(const mint &p) { // O(1)
        if ((x += p.x) >= mod()) x -= mod();
        return *this;
    }
    mint &operator-=(const mint &p) { // O(1)
        if ((x += mod() - p.x) >= mod()) x -= mod();
        return *this;
    }
    mint &operator*=(const mint &p) { // O(1)
        x = x * p.x % mod();
        return *this;
    }
    mint &operator/=(const mint &p) { // O(log mod)
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
        long long t; is >> t; a = mint(t); return (is);
    }

    mint inv() const { // O(log mod)
        assert(x != 0);
        return pow(mod() - 2); 
    }
    mint pow(long long n) const { // O(log n)
        assert(n >= 0);
        mint ret(1), mul(x);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }
};