template <class T>
struct HLD {
  vv<pair<T, ll>> g;
  ll n;
  vl siz, in, out, head, rev, par, dep;

  HLD(vv<pair<T, ll>> g, ll root = 0) : g(g), n(sz(g)), siz(n, 0), in(n, 0), out(n, 0), head(n, 0), rev(n, 0), par(n, 0), dep(n, 0) {
    dfs_siz(root, -1, 0);
    ll t = 0;
    head[root] = root;
    dfs_hld(root, -1, t);
  }

  // vのk個前の祖先を得る O(log N)
  ll last(ll v, ll k) {
    while (1) {
      ll u = head[v];
      if (in[v] - k >= in[u]) return rev[in[v] - k];
      k -= in[v] - in[u] + 1;
      v = par[u];
    }
  }

  ll lca(ll u, ll v) {
    for (;; v = par[head[v]]) {
      if (in[u] > in[v]) swap(u, v);
      if (head[u] == head[v]) return u;
    }
  }

  ll dist(ll u, ll v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

  template <class E>
  E query(ll u, ll v, E& ti, auto&& q, auto&& f, auto&& s, bool edge = false) {
    E l = ti, r = ti;
    for (;; v = par[head[v]]) {
      if (in[u] > in[v]) swap(u, v), swap(l, r);
      if (head[u] == head[v]) break;
      l = f(q(in[head[v]], in[v] + 1), l);
    }
    return s(f(q(in[u] + edge, in[v] + 1), l), r);
  }

  // E ti : モノイドの単位元
  // q(ll l, ll r) : [l, r)に対する区間クエリの結果を得る
  // f(E a, E b) : モノイドの演算
  auto query(ll u, ll v, auto&& ti, auto&& q, auto&& f, bool edge = false) {
    return query(u, v, ti, q, f, f, edge);
  }

  void add(ll u, ll v, auto&& q, bool edge = false) {
    for (;; v = par[head[v]]) {
      if (in[u] > in[v]) swap(u, v);
      if (head[u] == head[v]) break;
      q(in[head[v]], in[v] + 1);
    }
    q(in[u] + edge, in[v] + 1);
  }

  /* {parent, child} */
  vec<pll> compress(vl& remark) {
    auto cmp = [&](ll a, ll b) { return in[a] < in[b]; };
    sort(all(remark), cmp);
    remark.erase(unique(all(remark)), end(remark));
    ll K = sz(remark);
    for (ll k = 1; k < K; k++)
      remark.emplace_back(lca(remark[k - 1], remark[k]));
    sort(all(remark), cmp);
    remark.erase(unique(all(remark)), end(remark));
    vec<pll> es;
    stack<ll> st;
    for (auto& k : remark) {
      while (!st.empty() && out[st.top()] <= in[k]) st.pop();
      if (!st.empty()) es.emplace_back(st.top(), k);
      st.emplace(k);
    }
    return es;
  }

  void dfs_siz(ll idx, ll p, ll d) {
    dep[idx] = d;
    par[idx] = p;
    siz[idx] = 1;
    if (g[idx].size() && g[idx][0].second == p) swap(g[idx][0], g[idx].back());
    for (auto& e : g[idx]) {
      if (e.second == p) continue;
      dfs_siz(e.second, idx, d + 1);
      siz[idx] += siz[e.second];
      if (siz[g[idx][0].second] < siz[e.second]) swap(g[idx][0], e);
    }
  }

  void dfs_hld(ll idx, ll p, ll& times) {
    in[idx] = times++;
    rev[in[idx]] = idx;
    for (auto& [_, to] : g[idx]) {
      if (to == p) continue;
      head[to] = (g[idx][0].second == to ? head[idx] : to);
      dfs_hld(to, idx, times);
    }
    out[idx] = times;
  }
};
