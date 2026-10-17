//@aoj GRL_3_B

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
  auto bridges = lowlink.bridge;
  sort(all(bridges));
  for (auto [s, t] : bridges) cout << s << ' ' << t << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
