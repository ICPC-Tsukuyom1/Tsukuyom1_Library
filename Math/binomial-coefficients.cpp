/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/binomial-coefficients.cpp */
vec<mint> binom_fac, binom_inv;
vv<mint> pascal;
void init(ll n) {
  if (n <= 4500) {
    pascal = vv(n + 1, vec<mint>(n + 1, 0));
    pascal[0][0] = 1;
    reps(i, 1, n + 1) {
      pascal[i][0] = 1;
      reps(k, 1, i) { pascal[i][k] = pascal[i - 1][k - 1] + pascal[i - 1][k]; }
      pascal[i][i] = 1;
    }
    return;
  }
  binom_fac.assign(n + 1, 1);
  binom_inv.assign(n + 1, 1);
  reps(i, 1, n + 1) {
    binom_fac[i] = binom_fac[i - 1] * i;
    binom_inv[i] = binom_inv[i - 1] / i;
  }
}
mint com(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  if (pascal.size()) { return pascal[n][k]; }
  return binom_fac[n] * binom_inv[k] * binom_inv[n - k];
}