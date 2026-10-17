/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/binomial_coefficients.cpp */
template <class Mint>
struct Binom {
    vector<Mint> fac, finv;

    explicit Binom(int n) {
        assert(n >= 0);
        fac.resize(n + 1);
        finv.resize(n + 1);

        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * Mint(i);
        }
        finv[n] = fac[n].inv();
        for (int i = n; i >= 1; i--) {
            finv[i - 1] = finv[i] * Mint(i);
        }
    }

    Mint C(int n, int r) const {
        if (n < 0 || r < 0 || r > n) return Mint(0);
        assert(n < (int)fac.size());

        return fac[n] * finv[r] * finv[n - r];
    }

    Mint P(int n, int r) const {
        if (n < 0 || r < 0 || r > n) return Mint(0);
        assert(n < (int)fac.size());
        return fac[n] * finv[n - r];
    }
};