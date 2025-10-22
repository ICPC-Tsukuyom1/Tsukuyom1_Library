#include "modpow.cpp"
const ll mod = 998244353, root = 62;
void ntt(vl &a) {
  ll n = sz(a), L = 31 - __builtin_clz(n);
  static vl rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = {1, modpow(root, mod >> s, mod)};
    reps(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vl rev(n);
  rep(i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (ll k = 1; k < n; k *= 2) {
    for (ll i = 0; i < n; i += 2 * k) {
      rep(j, k) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
    }
  }
}

vl conv9(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = modpow(n, mod - 2, mod);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}