vector<pair<ll, ll>> prime_factorization(ll N) {
    vector<pair<ll, ll>>A;
    ll tmp = N;
    for (ll i = 2; i * i <= N; i++) {
        if (tmp % i == 0) {
            A.push_back({ i, 0 });
            while (tmp % i == 0) {
                A.back().second++;
                tmp /= i;
            }
        }
    }
    if (tmp != 1) A.push_back({ tmp, 1 });
    return A;
}
