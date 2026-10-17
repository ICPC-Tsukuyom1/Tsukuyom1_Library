/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/ntt.cpp */
// NTT (number theoretic transform)。畳み込みを mint 上の自由関数として提供する。
// depends on: modint
// 前提: mint::mod() は原始根 g をもつ素数で、(mint::mod() - 1) が 2 の冪で割り切れること。
// g を省略すると 3 を使う (998244353 / 167772161 / 469762049 等はこれでよい)。
template <class mint>
vec<mint> convolution(vec<mint> a, vec<mint> b, int g = 3) {
  if (a.empty() || b.empty()) return {};
  const int s = (int)sz(a) + (int)sz(b) - 1;
  int L = 0;
  while ((1 << L) < s) L++;
  const int n = 1 << L;
  assert((mint::mod() - 1) % n == 0);
  vec<mint> rt(2, 1);
  for (int k = 2, t = 2; k < n; k *= 2, t++) {
    rt.resize(n);
    mint r = mint(g).pow((mint::mod() - 1) >> t);
    reps(i, k, 2 * k) rt[i] = rt[i / 2] * ((i & 1) ? r : mint(1));
  }
  auto ntt = [&](vec<mint> &v) {
    vec<int> rev(n);
    rep(i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, n) if (i < rev[i]) swap(v[i], v[rev[i]]);
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k)
        rep(j, k) {
          mint z = rt[j + k] * v[i + j + k];
          mint &ai = v[i + j];
          v[i + j + k] = ai - z;
          ai += z;
        }
  };
  const mint inv_n = mint(n).inv();
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  vec<mint> out(n);
  rep(i, n) out[-i & (n - 1)] = a[i] * b[i] * inv_n;
  ntt(out);
  out.resize(s);
  return out;
}
