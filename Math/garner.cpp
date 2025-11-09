// depends on modula 演算

ll garner(vl a, vl p, ll mod) {
  const ll n = sz(a);
  vl kp(n + 1, 0), rmult(n + 1, 1);
  p.push_back(mod);
  rep(i, n) {
    ll x = modmul(a[i] - kp[i], modpow(rmult[i], p[i] - 2, p[i]), p[i]);
    x = (x < 0) ? (x + p[i]) : x;
    reps(j, i + 1, n + 1) {
      kp[j] = (kp[j] + modmul(rmult[j], x, p[j])) % p[j];
      rmult[j] = modmul(rmult[j], p[i], p[j]);
    }
  }
  return kp[n];
}