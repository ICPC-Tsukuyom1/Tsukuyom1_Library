//@yosupo point_set_range_composite

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#define T pair<mint, mint>
#define e \
  { 1, 0 }
#define op(a, b) \
  { a.first *b.first, a.second *b.first + b.second }

#include "../../../Structure/segtree.cpp"

int main() {
  ll n, q;
  in >> n >> q;

  SegTree seg(n);
  rep(i, n) {
    mint a, b;
    ll a_input, b_input;
    in >> a_input >> b_input;
    a = a_input;
    b = b_input;
    seg.update(i, {a, b});
  }
  while (q--) {
    ll t;
    in >> t;
    if (t == 0) {
      ll p, c, d;
      in >> p >> c >> d;
      seg.update(p, {c, d});
    } else {
      ll l, r, x;
      in >> l >> r >> x;
      auto &&[a, b] = seg.query(l, r);
      out << (a * x + b).x << '\n';
    }
  }
}