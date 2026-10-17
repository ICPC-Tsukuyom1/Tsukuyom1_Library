//@yosupo minimum_spanning_tree

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Graph/Kruskal.cpp"

int main() {
  ll n, m;
  in >> n >> m;
  vec<Edge> es(m);
  map<tuple<ll, ll, ll>, ll> rev;
  rep(i, m) {
    ll u, v, w;
    in >> u >> v >> w;
    es[i] = {u, v, w};
    rev[{u, v, w}] = i;
  }
  auto res = Kruskal(es, n);
  out << res.cost << '\n';
  for (auto e : res.edges) { out << rev[{e.from, e.to, e.cost}] << " "; }
  return 0;
}
