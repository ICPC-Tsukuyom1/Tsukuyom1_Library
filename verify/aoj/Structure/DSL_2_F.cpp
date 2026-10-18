//@aoj DSL_2_F

#include "../../../template.cpp"

#define T ll
#define e 2147483647
#define op(a, b) min(a, b)
#define F ll
#define id (-1)
#define merge(a, b) (b)
#define apply(f, x, len) (f)

#include "../../../Structure/lazysegtree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  LazySeg seg(n);
  while (q--) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll s, r, x;
      cin >> s >> r >> x;
      seg.effect(s, r + 1, x);
    } else {
      ll s, r;
      cin >> s >> r;
      cout << seg.query(s, r + 1) << '\n';
    }
  }
}
