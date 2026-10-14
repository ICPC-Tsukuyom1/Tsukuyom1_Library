//@yosupo lca

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Graph/lca.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  vv<ll> g(n);
  rep(i, n - 1) {
    ll p;
    in >> p;
    g[i + 1].emplace_back(p);
    g[p].emplace_back(i + 1);
  }
  LCA lca(g);
  lca.build();

  rep(Q, q) {
    ll u, v;
    in >> u >> v;
    out << lca.query(u, v) << "\n";
  }
}