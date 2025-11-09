// depends on modula 演算, MillerRabin, FastFactorize

ll rnd(ll l, ll r) {  //[l, r)
  random_device gen_seed;
  static mt19937_64 gen(gen_seed());
  return uniform_int_distribution<ll>(l, r - 1)(gen);
}
ll primroot(ll p) {
  auto v = fac(p - 1);
  sort(all(v));
  v.erase(unique(all(v)), end(v));
  while (1) {
    ll g = rnd(1, p);
    bool ok = true;
    for (auto d : v) {
      ll f = (p - 1) / d;
      if (modpow(g, f, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}