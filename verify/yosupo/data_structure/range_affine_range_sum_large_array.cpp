//@yosupo range_affine_range_sum_large_array

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#define T mint
#define e 0
#define F pair<mint, mint>
#define id \
  F { 1, 0 }
#define op(a, b) a + b
#define merge(a, b) \
  F { a.first *b.first, a.second *b.first + b.second }
#define apply(f, x, l) f.first* x + f.second* l

#include "../../../Structure/dynamic-lazysegtree.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  DynamicLazySeg seg(n);
  while (q--) {
    int type;
    in >> type;
    if (type == 0) {
      ll l, r, b, c;
      in >> l >> r >> b >> c;
      seg.effect(l, r, {b, c});
    } else {
      int l, r;
      in >> l >> r;
      out << seg.query(l, r).x << '\n';
    }
  }
}
