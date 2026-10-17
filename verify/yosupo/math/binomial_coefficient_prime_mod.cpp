//@yosupo binomial_coefficient_prime_mod

#include "../../../template.cpp"
#include "../../../Math/modint.cpp"
#include "../../../Math/binomial_coefficients.cpp"
#include "../../../Math/LucasBinom.cpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, m;
    cin >> t >> m;

    using mint = modint<0>;
    mint::set_mod(m);

    const int limit = min(m - 1, 10000100);
    LucasBinom<mint> binom(limit);

    while (t--) {
        int n, r;
        cin >> n >> r;
        cout << binom.C(n, r) << '\n';
    }
}