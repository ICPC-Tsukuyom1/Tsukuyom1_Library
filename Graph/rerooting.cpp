template <class T>
v(V) rerooting(Graph<T>& G)
{
  ll n = G.size();
  v(V) ans0(n);
  vector<v(E)> l_acc(n), r_acc(n);

  stack<tuple<ll, ll, bool>> dfs0;
  dfs0.push({0, -1, true});
  while (!dfs0.empty())
  {
    auto [i, p, first] = dfs0.top();
    dfs0.pop();
    if (first)
    {
      dfs0.push({i, p, false});
      for (auto& c : G[i])
      {
        if (c.to == p) continue;
        dfs0.push({c.to, i, true});
      }
    }
    else
    {
      v(E) cache;
      for (auto& c : G[i])
      {
        if (c.to == p) continue;
        cache.push_back(put_edge(ans0[c.to], c));
      }
      l_acc[i].push_back(ee);
      r_acc[i].push_back(ee);
      rep(j, cache.size()) l_acc[i].push_back(op(l_acc[i].back(), cache[j]));
      rrep(j, 0, cache.size()) r_acc[i].push_back(op(r_acc[i].back(), cache[j]));
      reverse(all(r_acc[i]));
      ans0[i] = put_vert(r_acc[i][0], i);
    }
  }

  v(V) ans(n);
  ans[0] = ans0[0];

  stack<tuple<ll, ll, E>> dfs;
  dfs.push({0, -1, ee});
  while (!dfs.empty())
  {
    auto [i, p, rev] = dfs.top();
    dfs.pop();

    ans[i] = put_vert(op(r_acc[i][0], rev), i);
    auto l = l_acc[i].begin(), r = r_acc[i].begin();
    for (auto& c : G[i])
    {
      if (c.to == p) continue;
      ++r;
      auto bottom = op((*l), (*r));
      ++l;
      auto merged = op(rev, bottom);
      auto verted = put_vert(merged, i);
      dfs.push({c.to, i, put_edge(verted, c)});
    }
  }
  return ans;
}
