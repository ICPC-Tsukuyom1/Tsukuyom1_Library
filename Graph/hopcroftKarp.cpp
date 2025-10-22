// usage: vl btoa(n, -1); ll matching = hopcroftKarp(g, btoa) / 2;
bool dfs(ll a, ll L, vv<ll>& g, vl& btoa, vl& A, vl& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (ll b : g[a])
    if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}
ll hopcroftKarp(vv<ll>& g, vl& btoa) {
  ll res = 0;
  vl A(sz(g)), B(sz(btoa)), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    cur.clear();
    for (ll a : btoa)
      if (a != -1) A[a] = -1;
    rep(a, sz(g)) if (A[a] == 0) cur.push_back(a);
    for (ll lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (ll a : cur)
        for (ll b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = 1;
          } else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.push_back(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (ll a : next) A[a] = lay;
      cur.swap(next);
    }
    rep(a, sz(g)) res += dfs(a, 0, g, btoa, A, B);
  }
}