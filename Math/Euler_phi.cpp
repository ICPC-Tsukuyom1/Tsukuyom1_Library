#include "FastFactorize.cpp"
ll Euler_phi(ll N) {
  vl A = fac(N);
  sort(all(A));
  A.erase(unique(all(A)), A.end());
  for (ll i = 0; i < sz(A); i++) { N /= A[i]; }
  for (ll i = 0; i < sz(A); i++) { N *= (A[i] - 1); }
  return N;
}