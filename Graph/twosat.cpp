struct Twosat {
  ll N;
  vv<ll> gr;
  vl values;
  Twosat(ll n = 0) : N(n), gr(2 * n) {}

  // (i = f) v (j = g) という条件を加える
  // i = f は、either(i, f, i, f)
  // (i = f) -> (j = g) は、either(i, !f, j, g)
  void either(ll i, bool f, ll j, bool g) {
    gr[i * 2 + (!f)].emplace_back(j * 2 + g);
    gr[j * 2 + (!g)].emplace_back(i * 2 + f);
    return;
  }

  vec<bool> satisfy() {
    SCC scc(gr);
    vec<bool> ret(N);
    vl idx = scc.cmp;
    rep(i, N) {
      if (idx[i * 2] == idx[i * 2 + 1]) return {};
      ret[i] = (idx[i * 2] < idx[i * 2 + 1]);
    }
    return ret;
  }
};