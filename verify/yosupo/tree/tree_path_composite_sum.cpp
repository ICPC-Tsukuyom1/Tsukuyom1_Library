//@yosupo tree_path_composite_sum

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

vec<mint> a;

#define V pair<mint, ll>
#define E pair<mint, ll>
#define put_edge(v, edge) \
  E { v[0] *edge.cost[0] + edge.cost[1] *v[1], v[1] }
#define put_vert(e, i) \
  V { e[0] + a[i], e[1] + 1 }
#define op(a, b) \
  E { a[0] + b[0], a[1] + b[1] }
#define ee \
  E { 0, 0 }

#include "../../../Graph/rerooting.cpp"

int main() {
  ll n;
  cin >> n;
  a.resize(n);
  rep(i, n) cin >> a[i];
  vv<Edge<pair<mint, mint>>> g(n);
  rep(i, n - 1) {
    ll u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    g[u].emplace_back(u, v, pair{b, c});
    g[v].emplace_back(v, u, pair{b, c});
  }
  auto res = rerooting(g);
  rep(i, n) { cout << res[i][0] << endl; }
}
