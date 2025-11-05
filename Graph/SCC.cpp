struct SCC {
  vv<ll>& g;
  vv<ll> dag, rg;
  vl cmp, ord;
  vec<bool> use;
  vv<ll> blng;

  SCC(vv<ll>& g) : g(g), use(sz(g), 0) { build(); }

  ll operator[](ll k) { return cmp[k]; }

  vl& belong(ll i) { return blng[i]; }

  void dfs(ll p) {
    if (use[p]) return;
    use[p] = 1;
    for (auto e : g[p]) dfs(e);
    ord.push_back(p);
  }

  void rdfs(ll p, ll cnt) {
    if (cmp[p] != -1) return;
    cmp[p] = cnt;
    for (auto e : rg[p]) rdfs(e, cnt);
  }

  void build() {
    rep(i, sz(g)) { dfs(i); }
    reverse(all(ord));
    use.clear(), use.shrink_to_fit();
    cmp.resize(sz(g), -1ll), rg.resize(sz(g));
    rep(i, sz(g)) {
      for (auto e : g[i]) { rg[e].emplace_back(i); }
    }
    ll ptr = 0;
    for (ll i : ord)
      if (cmp[i] == -1) rdfs(i, ptr), ptr++;
    rg.clear(), rg.shrink_to_fit();
    ord.clear(), ord.shrink_to_fit();
    dag.resize(ptr), blng.resize(ptr);
    rep(i, sz(g)) {
      blng[cmp[i]].push_back(i);
      for (auto& to : g[i]) {
        ll x = cmp[i], y = cmp[to];
        if (x == y) continue;
        dag[x].push_back(y);
      }
    }
  }
};