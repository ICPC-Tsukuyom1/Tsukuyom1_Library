vl toposort(vv<ll>& G) {
  vl ans;
  ll N = sz(G);
  vl ind(N);
  rep(i, N) {
    for (auto e : G[i]) { ind[e]++; }
  }
  queue<ll> Q;
  rep(i, N) {
    if (ind[i] == 0) Q.push(i);
  }
  while (!Q.empty()) {
    ll v = Q.front();
    ans.push_back(v);
    Q.pop();
    for (auto e : G[v]) {
      ind[e]--;
      if (ind[e] == 0) Q.push(e);
    }
  }
  return ans;
}