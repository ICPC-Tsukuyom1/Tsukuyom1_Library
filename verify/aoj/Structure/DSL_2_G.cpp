//@aoj DSL_2_G

#include "../../../template.cpp"

#define T ll
#define e 0LL
#define op(a, b) ((a) + (b))
#define F ll
#define id 0LL
#define merge(a, b) ((a) + (b))
#define apply(f, x, len) ((x) + (f) * (len))

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
      seg.effect(s - 1, r, x);
    } else {
      ll s, r;
      cin >> s >> r;
      cout << seg.query(s - 1, r) << '\n';
    }
  }
}
