//@aoj DSL_2_D

#include "../../../template.cpp"

#define F ll
#define id 2147483647
#define merge(a, b) ((b) == id ? (a) : (b))

#include "../../../Structure/dualsegtree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  DualSeg seg(n);
  while (q--) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll s, r, x;
      cin >> s >> r >> x;
      seg.effect(s, r + 1, x);
    } else {
      ll i;
      cin >> i;
      cout << seg.get(i) << '\n';
    }
  }
}
