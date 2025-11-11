// depends on modula 演算, MillerRabin, FastFactorize

ll Euler_phi(ll N) {
  vl A = fac(N);
  sort(all(A));
  A.erase(unique(all(A)), A.end());
  rep(i, sz(A)) N /= A[i];
  rep(i, sz(A)) N *= A[i] - 1;
  return N;
}