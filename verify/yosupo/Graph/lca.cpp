//@yosupo lca

#include "../../../template.cpp"
#include "../../../Graph/lca.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  vv<ll> g(n);
  rep(i, n - 1) {
    ll p;
    cin >> p;
    g[i + 1].emplace_back(p);
    g[p].emplace_back(i + 1);
  }
  LCA lca(g);
  lca.build();

  rep(Q, q) {
    ll u, v;
    cin >> u >> v;
    cout << lca.query(u, v) << "\n";
  }
}