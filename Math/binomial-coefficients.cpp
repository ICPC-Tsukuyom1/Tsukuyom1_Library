vec<mint> fac, inv;
vec<vec<mint>> pascal;
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
  fac.assign(n + 1, 1);
  inv.assign(n + 1, 1);
  reps(i, 1, n + 1) {
    fac[i] = fac[i - 1] * i;
    inv[i] = inv[i - 1] / i;
  }
}
mint com(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  if (pascal.size()) { return pascal[n][k]; }
  return fac[n] * inv[k] * inv[n - k];
}