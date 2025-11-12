//depends on; mint, Matrix
pair<ll, mint> Gauss(Matrix<mint>& a, bool LE = false) {
  ll n = a.n, m = a.m;
  ll rank = 0, je = m - LE;
  mint det = 1;
  rep(j, je) {
    ll idx = -1;
    reps(i, rank, n) {
      if (a[i][j].x) {
        idx = i; break;
      }
    }
    if (idx == -1) {
      det = 0; continue;
    }
    if (idx != rank) {
      det = -det, swap(a[idx], a[rank]);
    }
    det *= a[rank][j];
    if (LE && a[rank][j].x != 1) {
      mint coeff = a[rank][j].inv();
      reps(k, j, m) a[rank][k] *= coeff;
    }
    ll is = LE ? 0 : rank + 1;
    reps(i, is, n) {
      if (i == rank) continue;
      if (a[i][j].x) {
        mint coeff = a[i][j] / a[rank][j];
        reps(k, j, m) a[i][k] -= a[rank][k] * coeff;
      }
    }
    rank++;
  }
  return make_pair(rank, det);
}
vv<mint> solveLinear(Matrix<mint> a, vec<mint> b) {
  ll n = a.n, m = a.m;
  rep(i, n) a[i].push_back(b[i]);
  a.m++;
  auto p = Gauss(a, true);
  ll rank = p.first;
  reps(i, rank, n) {
    if (a[i][m].x) return vv<mint>(); // no solution
  }
  vv<mint> res(1, vec<mint>(m));
  vl piv(m, -1);
  ll j = 0;
  rep(i, rank) {
    while (a[i][j].x == 0) j++;
    res[0][j] = a[i][m], piv[j] = i;
  }
  rep(j, m) {
    if (piv[j] == -1) {
      vec<mint> x(m);
      x[j] = 1;
      rep(k, j) {
        if (piv[k] != -1) x[k] = -a[piv[k]][j];
      }
      res.push_back(x);
    }
  }
  return res;
}