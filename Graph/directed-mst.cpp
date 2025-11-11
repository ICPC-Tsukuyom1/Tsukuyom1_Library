// depends on: Undo可能UnionFind, Skew Heap

struct Edge {
  ll from, to, cost;
  auto operator<=>(const Edge& e) const { return cost <=> e.cost; }
  auto operator!() { return !cost; }
  auto operator+=(const Edge& e) { cost += e.cost; return *this; }
  auto operator-=(const Edge& e) { cost -= e.cost; return *this; }
  auto operator=(ll c) { cost = c; return *this; }
};

pair<ll, vl> directed_mst(int n, int r, vec<Edge>& g) {
  using H = SkewHeap<Edge>;
  UFRollback uf(n);
  vec<H*> heap(n);
  for (Edge e : g) heap[e.to] = H::merge(heap[e.to], new H(e));
  ll res = 0;
  vl seen(n, -1), path(n), par(n);
  seen[r] = r;
  vec<Edge> Q(n), in(n, {-1, -1}), comp;
  deque<tuple<ll, ll, vec<Edge>>> cycs;
  rep(s, n) {
    ll u = s, qi = 0, w;
    while (seen[u] < 0) {
      if (!heap[u]) return {-1, {}};
      Edge e = heap[u]->top();
      heap[u]->laz -= {0, 0, e.cost}, heap[u] = H::pop(heap[u]);
      Q[qi] = e, path[qi++] = u, seen[u] = s;
      res += e.cost, u = uf.root(e.from);
      if (seen[u] == s) {
        H* cyc = 0;
        int end = qi, time = uf.time();
        do cyc = H::merge(cyc, heap[w = path[--qi]]);
        while (uf.unite(u, w));
        u = uf.root(u), heap[u] = cyc, seen[u] = -1;
        cycs.push_front({u, time, {&Q[qi], &Q[end]}});
      }
    }
    rep(i, qi) in[uf.root(Q[i].to)] = Q[i];
  }
  // optional (for par)
  for (auto& [u, t, comp] : cycs) {
    uf.rollback(t);
    Edge inEdge = in[u];
    for (auto& e : comp) in[uf.root(e.to)] = e;
    in[uf.root(inEdge.to)] = inEdge;
  }
  rep(i, n) par[i] = in[i].from;
  return {res, par};
}
