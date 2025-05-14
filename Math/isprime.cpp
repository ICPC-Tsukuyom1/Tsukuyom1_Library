bool isprime(ll N) {
    if (N < 2) return false;
    for (ll i = 2; i * i <= N; i++) {
        if (N % i == 0) return false;
    }
    return true;
}
