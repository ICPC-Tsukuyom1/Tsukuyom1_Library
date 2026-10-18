//@aoj GRL_5_B

#include "../../../template.cpp"

#define V ll
#define E ll
#define put_edge(v, edge) ((v) + (edge).cost)
#define put_vert(e, i) (e)
#define op(a, b) max(a, b)
#define ee 0ll

#include "../../../Graph/rerooting.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  vv<Edge<ll>> g(n);
  rep(i, n - 1) {
    ll s, t, w;
    cin >> s >> t >> w;
    g[s].emplace_back(s, t, w);
    g[t].emplace_back(t, s, w);
  }
  auto res = rerooting(g);
  rep(i, n) cout << res[i] << '\n';
}
