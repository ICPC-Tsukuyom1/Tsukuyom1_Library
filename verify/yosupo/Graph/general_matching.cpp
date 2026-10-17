//@yosupo general_matching

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Graph/maxMatching.cpp"
void solve() {
  ll n, m;
  in >> n >> m;
  vv<ll> g(n);
  rep(i, m) {
    ll u, v;
    in >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  maxMatch a(g);
  auto ans = a.max_match();
  out << sz(ans) << '\n';
  rep(i, sz(ans)) { out << ans[i][0] << ' ' << ans[i][1] << '\n'; }
}
int main() {
  ll T = 1;
  while (T--) solve();
}