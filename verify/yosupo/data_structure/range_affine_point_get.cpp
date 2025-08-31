//@yosupo range_affine_point_get

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

#define F pair<mint, mint>
#define id F{1, 0}
#define merge(a, b) F{a.first * b.first, a.second * b.first + b.second}

#include "../../../Structure/dualsegtree.cpp"
int main() {
  int n, q;
  cin >> n >> q;
  DualSeg seg(n);
  vec<mint> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      ll l, r, b, c;
      cin >> l >> r >> b >> c;
      seg.effect(l, r, {b, c});
    } else {
      int i;
      cin >> i;
      auto [p, q] = seg.get(i);
      cout << a[i] * p + q << endl;
    }
  }
}