//@aoj GRL_4_A

#include "../../../template.cpp"
#include "../../../Graph/topological.cpp"

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
  cout << (sz(toposort(g)) < V) << '\n';
}
