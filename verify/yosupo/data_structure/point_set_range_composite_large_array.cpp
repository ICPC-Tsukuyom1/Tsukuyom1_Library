//@yosupo point_set_range_composite_large_array

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

#define T pair<mint, mint>
#define e \
  { 1, 0 }
#define op(a, b) \
  { a.first *b.first, a.second *b.first + b.second }

#include "../../../Structure/dynamic-segtree.cpp"

int main() {
  ll n, q;
  in >> n >> q;

  DynamicSeg seg(n);
  // rep(i, n)
  // {
  //   mint a, b;
  //   ll a_input, b_input;
  //   in >> a_input >> b_input;
  //   a = a_input;
  //   b = b_input;
  //   seg.update(i, {a, b});
  // }
  // rep(i, n)
  // {
  //   out << seg.query(i, i+1).first.x << " " << seg.query(i, i+1).second.x <<
  //   '\n';
  // }
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
