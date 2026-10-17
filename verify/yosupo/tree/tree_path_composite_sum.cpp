//@yosupo tree_path_composite_sum

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

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
  in >> n;
  a.resize(n);
  rep(i, n) {
    ll a_input;
    in >> a_input;
    a[i] = a_input;
  }
  vv<Edge<pair<mint, mint>>> g(n);
  rep(i, n - 1) {
    ll u, v;
    mint b, c;
    ll b_input, c_input;
    in >> u >> v >> b_input >> c_input;
    b = b_input;
    c = c_input;
    g[u].emplace_back(u, v, pair{b, c});
    g[v].emplace_back(v, u, pair{b, c});
  }
  auto res = rerooting(g);
  rep(i, n) { out << res[i].first.x << '\n'; }
}
