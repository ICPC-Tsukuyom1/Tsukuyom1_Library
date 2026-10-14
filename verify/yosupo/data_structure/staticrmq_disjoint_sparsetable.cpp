//@yosupo staticrmq

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#define T int
#define op(a, b) min(a, b)

#include "../../../Structure/disjoint-sparsetable.cpp"

int main() {
  int n, q;
  in >> n >> q;
  vec<int> a(n);
  rep(i, n) { in >> a[i]; }
  DisjointSparseTable dst(a);
  rep(i, q) {
    int l, r;
    in >> l >> r;
    out << dst.fold(l, r) << "\n";
  }
  return 0;
}
