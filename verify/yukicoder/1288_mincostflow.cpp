//@yukicoder 1288

#include "../../template.cpp"
#include "../../Graph/mincostflow.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  string s;
  cin >> n >> s;
  vl v(n);
  rep(i, n) cin >> v[i];

  vv<ll> nxt(4, vl(n, n));
  rrep(i, 0, n) {
    if (i != n - 1) rep(j, 4) chmin(nxt[j][i], nxt[j][i + 1]);
    if (i == 0) continue;
    rep(j, 4) if (s[i] == "yuki"[j]) nxt[j][i - 1] = i;
  }

  MinCostFlow mcf(n + 2);

  mcf.add_edge(n, s[0] == 'y' ? 0 : nxt[0][0], 1e18, 0);

  rep(i, n) {
    rep(j, 4) if (s[i] == "yuki"[j] && nxt[j][i] < n)
        mcf.add_edge(i, nxt[j][i], 1e18, 0);
    rep(j, 3) if (s[i] == "yuki"[j] && nxt[j + 1][i] < n)
        mcf.add_edge(i, nxt[j + 1][i], 1, -v[i]);
    if (s[i] == 'i') mcf.add_edge(i, n + 1, 1, -v[i]);
  }

  mcf.setpi(n);

  auto res = mcf.slope(n, n + 1);

  ll ans = 0;
  for (auto [l, r] : res) { chmax(ans, -r); }

  cout << ans << endl;
}
