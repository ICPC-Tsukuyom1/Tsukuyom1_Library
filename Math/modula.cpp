ll modmul(ll a, ll b, ll mod) { return __int128(a) * b % mod; }
ll modpow(ll a, ll b, ll mod) {
  ll ans = 1;
  for (; b; a = modmul(a, a, mod), b /= 2)
    if (b & 1) ans = modmul(ans, a, mod);
  return ans;
}
// a^x == b (mod p), if no such x exists than -1
ll modlog(ll a, ll b, ll p) {
  ll n = (ll)sqrtl(p) + 1, e = 1, f = 1, j = 1;
  unordered_map<ll, ll> A;
  while (j = n && (e = f = e * a % p) != b % p) A[e * b % p] = j++;
  if (e == b % p) return j;
  if (gcd(p, e) == gcd(p, b))
    reps(i, 2, n + 2) if (A.count(e = e * f % p)) return n * i - A[e];
  return -1;
}
// x^2 == a (mod p)
ll modsqrt(ll a, ll p) {
  a %= p;
  while (a < 0) a += p;
  if (a == 0) return 0;
  if (modpow(a, (p - 1) / 2, p) != 1) return -1;
  if (p % 4 == 3) return modpow(a, (p + 1) / 4, p);
  ll s = p - 1, n = 2;
  ll r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  while (modpow(n, (p - 1) / 2, p) != p - 1) ++n;
  ll x = modpow(a, (s + 1) / 2, p);
  ll b = modpow(a, s, p), g = modpow(n, s, p);
  for (;; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; ++m) t = modmul(t, t, p);
    if (m == 0) return x;
    ll gs = modpow(g, 1ll << (r - m - 1), p);
    g = modmul(gs, gs, p);
    x = modmul(x, gs, p);
    b = modmul(b, g, p);
  }
}
ll modinv(ll x, ll mod) { return modpow(x, mod - 2, mod); }