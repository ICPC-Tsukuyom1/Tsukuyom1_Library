ll modmul(ll a, ll b, ll mod) {
	ll ret = a * b - mod * ll(1.L / mod * a * b);
	return ret + mod * (ret < 0) - mod * (ret >= mod);
}
ll modpow(ll a, ll b, ll mod) {
	ll ans = 1;
	for(; b; a = modmul(a, a, mod), b /= 2)
		if (b & 1) ans = modmul(ans, a, mod);
	return ans;
}
bool isprime(ll n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ll a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
    for (ll m : a) {
        ll p = modpow(m % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = (p * p) % n;
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}