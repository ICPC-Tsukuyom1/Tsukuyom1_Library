struct LCA {
    ll Log;
    vector<ll> dep;
    Graph &G;
    vector<vector<ll>>table;
    LCA(Graph &G) : G(G), dep(G.size()), Log(32 - __builtin_clz(G.size())) {
        table.assign(Log, vector<ll>(G.size(),-1));
    }
    void dfs(ll idx, ll par, ll d) {
        table[0][idx] = par;  dep[idx] = d;
        for (auto to : G[idx]) {
            if (to.to != par) dfs(to.to, idx, d + 1);
        }
    }
    void build() {
        dfs(0, -1, 0);
        for (ll k = 0; k + 1 < Log; k++) {
            for (ll i = 0; i < table[k].size(); i++) {
                if (table[k][i] == -1) table[k+1][i] = -1;
                else table[k+1][i] = table[k][table[k][i]];
            }
        }
    }
    ll query(ll u, ll v) {
        if (dep[u] > dep[v]) swap(u, v);
        for (ll i = Log - 1; i >= 0; i--) {
            if (((dep[v] - dep[u]) >> i) & 1) v = table[i][v];
        }  if (u == v) return u;
        for (ll i = Log - 1; i >= 0; i--) {
            if (table[i][u] != table[i][v]) { u = table[i][u]; v = table[i][v];  }
        }  return table[0][u];
    }
};
