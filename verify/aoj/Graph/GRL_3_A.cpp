//@aoj GRL_3_A

#include "../../../template.cpp"
#include "../../../Graph/LowLink.cpp"

static void solve() {
  ll V, E;
  cin >> V >> E;
  vv<ll> g(V);
  rep(i, E) {
    ll s, t;
    cin >> s >> t;
    g[s].push_back(t);
    g[t].push_back(s);
  }
  LowLink<vv<ll>> lowlink(g);
  auto arti = lowlink.arti;
  sort(all(arti));
  for (ll v : arti) cout << v << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
