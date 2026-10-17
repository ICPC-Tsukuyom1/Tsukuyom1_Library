//@yosupo directedmst

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Structure/skew-heap.cpp"
#include "../../../Structure/UnionFind-rollback.cpp"
#include "../../../Graph/directed-mst.cpp"

int main() {
  ll n, m, s;
  in >> n >> m >> s;
  vec<Edge> g;
  rep(i, m) {
    ll a, b, c;
    in >> a >> b >> c;
    g.emplace_back(a, b, c);
  }
  auto [cost, par] = directed_mst(n, s, g);
  out << cost << "\n";
  rep(i, n) {
    out << (i == s ? s : par[i]) << " \n"[i == n-1];
  }
}