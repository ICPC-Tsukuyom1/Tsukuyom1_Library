//@yukicoder 3277

#include "../../template.cpp"

#define T ll
#define e 0LL
#define op(a, b) ((a) + (b))

#include "../../Structure/segtree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  if (!(cin >> n >> q)) return 0;
  SegTree seg(n);
  rep(i, n) {
    ll x;
    cin >> x;
    seg.update(i, x);
  }
  rep(_, q) {
    int t;
    cin >> t;
    if (t == 0) {
      int i;
      ll x;
      cin >> i >> x;
      seg.update(i, x);
    } else {
      ll x;
      cin >> x;
      auto r = seg.max_right([&](ll s) { return s <= x; });
      cout << r << '\n';
    }
  }
  return 0;
}
