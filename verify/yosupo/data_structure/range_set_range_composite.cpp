//@yosupo range_set_range_composite

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#define T pair<mint, mint>
#define e \
  T { 1, 0 }
#define F pair<mint, mint>
#define id \
  F { 0, 0 }
#define op(a, b) \
  T { a.first *b.first, a.second *b.first + b.second }

T pow_fn(T fn, ll n) {
  T ans = e;
  while (n > 0) {
    if (n & 1) ans = op(ans, fn);
    fn = op(fn, fn);
    n >>= 1;
  }
  return ans;
}

#define merge(a, b) b.first == 0 ? a : b
#define apply(f, x, l) f.first == 0 ? x : pow_fn(f, l)

#include "../../../Structure/lazysegtree.cpp"

int main() {
  int n, q;
  in >> n >> q;
  auto *seg = new LazySeg(n);
  rep(i, n) {
    ll a, b;
    in >> a >> b;
    seg->effect(i, i + 1, {a, b});
  }
  while (q--) {
    int type;
    in >> type;
    if (type == 0) {
      ll l, r, c, d;
      in >> l >> r >> c >> d;
      seg->effect(l, r, {c, d});
    } else {
      int l, r, x;
      in >> l >> r >> x;
      auto [a, b] = seg->query(l, r);
      out << (a * x + b).x << '\n';
    }
  }
}
