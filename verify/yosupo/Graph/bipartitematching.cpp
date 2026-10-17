//@yosupo bipartitematching

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Graph/hopcroftKarp.cpp"
void solve() {
  ll L, R, M;
  in >> L >> R >> M;
  vv<ll> g(L + R);
  rep(i, M) {
    ll a, b;
    in >> a >> b;
    b += L;
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }
  vl btoa(L + R, -1);
  out << hopcroftKarp(g, btoa) / 2 << '\n';
  rep(i, L) {
    if (btoa[i] != -1) { out << i << ' ' << btoa[i] - L << '\n'; }
  }
}
int main() {
  ll T = 1;
  while (T--) solve();
}