//@yosupo staticrmq

#include "../../../template.cpp"

const ll INF = 4e18;

#define T ll
#define e INF
#define op(a, b) min(a, b)

#include "../../../Structure/segtree.cpp"

int main() {
  int n, q;
  cin >> n >> q;
  SegTree seg(n);
  rep(i, n) {
    int x;
    cin >> x;
    seg.update(i, x);
  }
  rep(i, q) {
    int l, r;
    cin >> l >> r;
    cout << seg.query(l, r) << endl;
  }
  return 0;
}
