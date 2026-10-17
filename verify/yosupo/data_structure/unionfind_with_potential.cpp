//@yosupo unionfind_with_potential

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

const ll mod = 998244353;

#include "../../../Math/modint.cpp"
#include "../../../Structure/weightedunionfind.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  WeightedUnionFind<mint> uf(n);
  while (q--) {
    ll t, u, v;
    in >> t >> u >> v;
    if (t == 0) {
      mint x;
      ll x_input;
      in >> x_input;
      x = x_input;
      if (uf.find(u) == uf.find(v)) {
        if (uf.weight(u) - uf.weight(v) != x) {
          out << 0 << '\n';
          continue;
        }
      }
      uf.merge(v, u, x);
      out << 1 << '\n';
    } else {
      if (uf.find(u) == uf.find(v)) {
        out << (uf.weight(u) - uf.weight(v)).x << '\n';
      } else {
        out << -1 << '\n';
      }
    }
  }
}