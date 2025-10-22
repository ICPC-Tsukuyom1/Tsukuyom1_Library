#include "MillerRabin.cpp"

ll pollard(ll n) {
  ll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ll x) { return modmul(x, x, n) + i; };
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
vl fac(ll n) {
  if (n == 1) return {};
  if (isprime(n)) return {n};
  ll x = pollard(n);
  auto l = fac(x), r = fac(n / x);
  l.insert(l.end(), all(r));
  return l;
}