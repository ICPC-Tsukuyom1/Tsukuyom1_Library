template <class T, bool onEdge = false>
struct HLD {
  vv<ll> g;
  ll n, tim = 0;
  vl par, siz, rt, pos;

  // gは親→子の辺のみをもつグラフ
  HLD(vv<ll> g) : g(g), n(sz(g)), par(n, -1), siz(n, 1), rt(n), pos(n) {
    dfs_siz(0);
    dfs_hld(0);
  }

  void dfs_siz(ll v) {
    if (par[v] != -1) g[v].erase(find(all(g[v]), par[v]));
    for (ll& u : g[v]) {
      par[u] = v;
      dfs_siz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[g[v][0]]) swap(u, g[v][0]);
    }
  }

  void dfs_hld(ll v) {
    pos[v] = tim++;
    for (ll u : g[v]) {
      rt[u] = (u == g[v][0] ? rt[v] : u);
      dfs_hld(u);
    }
  }

  void process(ll u, ll v, auto&& op) {
    for (; rt[u] != rt[v]; v = par[rt[v]]) {
      if (pos[rt[u]] > pos[rt[v]]) swap(u, v);
      op(pos[rt[v]], pos[v] + 1);
    }
    if (pos[u] > pos[v]) swap(u, v);
    op(pos[u] + onEdge, pos[v] + 1);
  }

  T queryPath(ll u, ll v, T e, auto&& get, auto&& op) {
    T res = e;
    process(u, v, [&](ll l, ll r) { res = op(res, get(l, r)); });
    return res;
  }

  T querySubtree(ll v, auto&& get) {
    return get(pos[v] + onEdge, pos[v] + siz[v]);
  }
};
