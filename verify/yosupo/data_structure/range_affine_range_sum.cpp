//@yosupo range_affine_range_sum

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

#define T mint
#define e 0
#define F pair<mint, mint>
#define id F{1, 0}
#define op(a, b) a+b
#define merge(a, b) F{a.first * b.first, a.second * b.first + b.second}
#define apply(f, x, l) f.first * x + f.second * l

#include "../../../Structure/lazysegtree.cpp"

int main() {
  int n, q;
  cin >> n >> q;
  LazySeg seg(n);
  rep(i, n) {
    ll x;
    cin >> x;
    seg.effect(i, i + 1, {0, x});
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      ll l, r, b, c;
      cin >> l >> r >> b >> c;
      seg.effect(l, r, {b, c});
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.query(l, r) << endl;
    }
  }
}