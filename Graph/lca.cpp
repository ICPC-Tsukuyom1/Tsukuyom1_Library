struct LCA {
  ll Log;
  vl dep;
  vv<ll>& G;
  vv<ll> table;
  LCA(vv<ll>& G) : G(G), dep(G.size()), Log(bit_width(G.size())) {
    table.assign(Log, vl(G.size(), -1));
  }
  void dfs(ll idx, ll par, ll d) {
    table[0][idx] = par;
    dep[idx] = d;
    for (auto to : G[idx]) {
      if (to != par) dfs(to, idx, d + 1);
    }
  }
  void build() {  // initialize (you must run it before accept some queries)
    dfs(0, -1, 0);
    rep(k, Log - 1) {
      rep(i, table[k].size()) {
        if (table[k][i] == -1) table[k + 1][i] = -1;
        else table[k + 1][i] = table[k][table[k][i]];
      }
    }
  }
  ll query(ll u, ll v) {
    if (dep[u] > dep[v]) swap(u, v);
    rrep(i, 0, Log) {
      if (((dep[v] - dep[u]) >> i) & 1) v = table[i][v];
    }
    if (u == v) return u;
    rrep(i, 0, Log) {
      if (table[i][u] != table[i][v]) {
        u = table[i][u];
        v = table[i][v];
      }
    }
    return table[0][u];
  }
};
