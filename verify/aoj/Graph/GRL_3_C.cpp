//@aoj GRL_3_C

#include "../../../template.cpp"
#include "../../../Graph/SCC.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll V, E;
  cin >> V >> E;
  vv<ll> g(V);
  rep(i, E) {
    ll s, t;
    cin >> s >> t;
    g[s].push_back(t);
  }
  SCC scc(g);
  ll Q;
  cin >> Q;
  while (Q--) {
    ll u, v;
    cin >> u >> v;
    cout << (scc[u] == scc[v]) << '\n';
  }
}
