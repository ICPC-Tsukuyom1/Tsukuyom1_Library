//@yosupo range_affine_point_get

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#define F pair<mint, mint>
#define id \
  F { 1, 0 }
#define merge(a, b) \
  F { a.first *b.first, a.second *b.first + b.second }

#include "../../../Structure/dynamic-dualsegtree.cpp"

int main() {
  int n, q;
  in >> n >> q;
  DynamicDualSeg seg(n);
  vec<mint> a(n);
  rep(i, n) {
    ll a_input;
    in >> a_input;
    a[i] = a_input;
  }
  while (q--) {
    int type;
    in >> type;
    if (type == 0) {
      ll l, r, b, c;
      in >> l >> r >> b >> c;
      seg.effect(l, r, {b, c});
    } else {
      int i;
      in >> i;
      auto [p, q] = seg.get(i);
      out << (a[i] * p + q).x << '\n';
    }
  }
}
