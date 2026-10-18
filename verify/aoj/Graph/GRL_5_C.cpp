//@aoj GRL_5_C

#include "../../../template.cpp"
#include "../../../Graph/lca.cpp"

static void solve() {
  ll n;
  cin >> n;
  vv<ll> g(n);
  rep(i, n) {
    ll k;
    cin >> k;
    rep(j, k) {
      ll c;
      cin >> c;
      g[i].push_back(c);
      g[c].push_back(i);
    }
  }
  LCA lca(g);
  lca.build();
  ll q;
  cin >> q;
  while (q--) {
    ll u, v;
    cin >> u >> v;
    cout << lca.query(u, v) << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
