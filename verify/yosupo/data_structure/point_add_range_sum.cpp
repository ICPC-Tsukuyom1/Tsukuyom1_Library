//@yosupo point_add_range_sum

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#define T ll
#define e 0
#define op(a, b) a + b

#include "../../../Structure/segtree.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  SegTree seg(n);
  rep(i, n) {
    ll a;
    in >> a;
    seg.update(i, a);
  }
  while (q--) {
    ll t;
    in >> t;
    if (t == 0) {
      ll p, x;
      in >> p >> x;
      seg.update(p, seg.query(p, p + 1) + x);
    } else {
      ll l, r;
      in >> l >> r;
      out << seg.query(l, r) << '\n';
    }
  }
}
