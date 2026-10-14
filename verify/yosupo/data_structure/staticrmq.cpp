//@yosupo staticrmq

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

const ll INF = 4e18;

#define T ll
#define e INF
#define op(a, b) min(a, b)

#include "../../../Structure/segtree.cpp"

int main() {
  int n, q;
  in >> n >> q;
  SegTree seg(n);
  rep(i, n) {
    int x;
    in >> x;
    seg.update(i, x);
  }
  rep(i, q) {
    int l, r;
    in >> l >> r;
    out << seg.query(l, r) << '\n';
  }
  return 0;
}
