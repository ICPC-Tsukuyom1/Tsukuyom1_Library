struct Twosat {
  ll N;
  Graph gr;
  vl values;
  Twosat(ll n = 0) : N(n), gr(2 * n) {}

  // (i = f) v (j = g) という条件を加える
  // i = f は、either(i, f, i, f)
  // (i = f) -> (j = g) は、either(i, !f, j, g)
  void either(ll i, bool f, ll j, bool g) {
    gr.add(i * 2 + (!f), j * 2 + g, 1, 1);
    gr.add(j * 2 + (!g), i * 2 + f, 1, 1);
    return;
  }

  vec<bool> satisfy() {
    SCC scc(gr);
    scc.build();
    vec<bool> ret(N);
    vl idx = scc.cmp;
    rep(i, N) {
      if (idx[i * 2] == idx[i * 2 + 1]) return {};
      ret[i] = (idx[i * 2] < idx[i * 2 + 1]);
    }
    return ret;
  }
};