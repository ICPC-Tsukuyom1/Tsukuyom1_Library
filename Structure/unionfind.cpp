struct UnionFind {
  vl info;
  UnionFind(ll n) : info(n, -1LL) {}
  ll root(ll v) {
    if (info[v] < 0) return v;
    return info[v] = root(info[v]);
  }
  bool unite(ll u, ll v) {
    u = root(u), v = root(v);
    if (u == v) return false;
    if (-info[u] < -info[v]) swap(u, v);
    info[u] += info[v];
    info[v] = u;
    return true;
  }
  ll size(ll v) { return -info[root(v)]; }
};