//@yosupo static_range_sum

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#define T ll
#define op(a, b) a + b

#include "../../../Structure/disjoint-sparsetable.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  vl a(n);
  rep(i, n) in >> a[i];
  DisjointSparseTable dst(a);
  while (q--) {
    ll l, r;
    in >> l >> r;
    out << dst.fold(l, r) << '\n';
  }
}
