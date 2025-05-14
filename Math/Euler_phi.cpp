ll Euler_phi(ll N) {
    vector<pair<ll, ll>>A = prime_factorization(N);
    for (ll i = 0; i < A.size(); i++) {
        N /= A[i].first;
    }
    for (ll i = 0; i < A.size(); i++) {
        N *= (A[i].first - 1);
    }
    return N;
}
