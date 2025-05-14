ll power(ll N, ll M, ll p) {
    ll ans = 1;
    while (M > 0) {
        if (M & 1) ans = ans * N % p;
        N = N * N % p;
        M >>= 1;
    }
    return ans;
}
