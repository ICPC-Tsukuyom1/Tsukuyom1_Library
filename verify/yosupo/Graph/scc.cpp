//@yosupo scc
#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Graph/SCC.cpp"
void solve() {
  ll n, m;
  in >> n >> m;
  vv<ll> g(n);
  rep(i, m) {
    ll u, v;
    in >> u >> v;
    g[u].emplace_back(v);
  }
  SCC scc(g);
  out << sz(scc.dag) << '\n';
  rep(i, sz(scc.dag)) {
    out << sz(scc.belong(i));
    for (auto &e : scc.belong(i)) { out << ' ' << e; }
    out << '\n';
  }
}
int main() {
  ll T = 1;
  while (T--) solve();
}