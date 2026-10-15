//@yosupo tree_path_composite_sum

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

vec<mint> a;

#define V pair<mint, ll>
#define E pair<mint, ll>
#define put_edge(v, edge) \
  E { v.first *edge.cost.first + edge.cost.second *v.second, v.second }
#define put_vert(e, i) \
  V { e.first + a[i], e.second + 1 }
#define op(a, b) \
  E { a.first + b.first, a.second + b.second }
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
  rep(i, n) { cout << res[i].first << endl; }
}
