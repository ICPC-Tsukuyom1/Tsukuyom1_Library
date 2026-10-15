/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/Graph/minimum_spanning_tree.cpp */
//@yosupo minimum_spanning_tree

#include "../../../template.cpp"
#include "../../../Graph/Kruskal.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;
  vec<Edge> es(m);
  map<tuple<ll, ll, ll>, ll> rev;
  rep(i, m) {
    ll u, v, w;
    cin >> u >> v >> w;
    es[i] = {u, v, w};
    rev[{u, v, w}] = i;
  }
  auto res = Kruskal(es, n);
  cout << res.cost << '\n';
  for (auto e : res.edges) { cout << rev[{e.from, e.to, e.cost}] << " "; }
  return 0;
}
