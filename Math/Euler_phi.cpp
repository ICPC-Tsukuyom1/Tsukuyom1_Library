#include "FastFactorize.cpp"
ll Euler_phi(ll N) {
    vl A = fac(N); sort(all(A));
    A.erase(unique(all(A)), A.end());
    for (ll i = 0; i < A.size(); i++) {
        N /= A[i].first;
    }
    for (ll i = 0; i < A.size(); i++) {
        N *= (A[i].first - 1);
    }
    return N;
}