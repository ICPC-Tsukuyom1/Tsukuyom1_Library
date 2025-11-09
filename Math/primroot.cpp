#include "../random.cpp"
#include "FastFactorize.cpp"
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