//@yosupo point_set_range_composite_large_array

#include "../../../template.cpp"

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
  cin >> n >> q;

  DynamicSeg seg(n);
  // rep(i, n)
  // {
  //   mint a, b;
  //   cin >> a >> b;
  //   seg.update(i, {a, b});
  // }
  // rep(i, n)
  // {
  //   cout << seg.query(i, i+1).first << " " << seg.query(i, i+1).second <<
  //   endl;
  // }
  while (q--) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll p, c, d;
      cin >> p >> c >> d;
      seg.update(p, {c, d});
    } else {
      ll l, r, x;
      cin >> l >> r >> x;
      auto&& [a, b] = seg.query(l, r);
      cout << a * x + b << '\n';
    }
  }
}
