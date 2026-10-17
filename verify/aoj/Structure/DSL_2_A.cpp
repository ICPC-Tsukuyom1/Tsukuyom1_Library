//@aoj DSL_2_A

#include "../../../template.cpp"

#define T ll
#define e 2147483647
#define op(a, b) min(a, b)

#include "../../../Structure/segtree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  SegTree seg(n);
  while (q--) {
    ll com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      seg.update(x, y);
    } else {
      cout << seg.query(x, y + 1) << '\n';
    }
  }
}
