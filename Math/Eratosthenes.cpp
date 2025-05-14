struct Eratosthenes {
    vector<bool>prime;
    vector<ll>p;

    Eratosthenes(ll N) : prime(N + 1, true), p(N + 1, 0) {
        prime[0] = prime[1] = false;
        for (ll i = 2; i <= N; i++) {
            if (!prime[i]) continue;
            p[i]++;
            ll tmp = 2 * i;
            while (tmp <= N) {
                prime[tmp] = false;
                tmp += i;
            }
        }
        for (ll i = 1; i <= N; i++) {
            p[i] += p[i - 1];
        }
    }

    ll count(ll limit) { //[1, limit]
        assert(limit <= N);
        return p[limit];
    }
};
