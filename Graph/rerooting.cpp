template <class T>
vec<V> rerooting(Graph<T>& G) {
  ll n = G.size();
  vec<V> ans0(n);
  vv<E> l_acc(n), r_acc(n);
  auto dfs0 = [&](auto&& f, ll i, ll p) -> void {
    vec<E> cache;
    for (auto& c : G[i]) {
      if (c.to == p) continue;
      f(f, c.to, i);
      cache.push_back(put_edge(ans0[c.to], c));
    }
    l_acc[i].push_back(ee);
    r_acc[i].push_back(ee);
    rep(j, cache.size()) l_acc[i].push_back(op(l_acc[i].back(), cache[j]));
    rrep(j, 0, cache.size()) r_acc[i].push_back(op(r_acc[i].back(), cache[j]));
    reverse(all(r_acc[i]));
    ans0[i] = put_vert(r_acc[i][0], i);
  };
  dfs0(dfs0, 0, -1);
  vec<V> ans(n);
  ans[0] = ans0[0];
  auto dfs = [&](auto&& f, ll i, ll p, E rev) -> void {
    ans[i] = put_vert(op(r_acc[i][0], rev), i);
    auto l = l_acc[i].begin(), r = r_acc[i].begin();
    for (auto& c : G[i]) {
      if (c.to == p) continue;
      ++r;
      auto bottom = op((*l), (*r));
      ++l;
      auto merged = op(rev, bottom);
      auto verted = put_vert(merged, i);
      f(f, c.to, i, put_edge(verted, c));
    }
  };
  dfs(dfs, 0, -1, ee);
  return ans;
}
