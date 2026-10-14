//@yosupo unionfind

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/unionfind.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  UnionFind uf(n);
  while (q--) {
    ll t, u, v;
    in >> t >> u >> v;
    if (t == 0) {
      uf.unite(u, v);
    } else {
      out << (uf.root(u) == uf.root(v)) << '\n';
    }
  }
}