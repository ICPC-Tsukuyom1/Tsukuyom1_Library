//@aoj DSL_2_E

#include "../../../template.cpp"

#define F ll
#define id 0LL
#define merge(a, b) ((a) + (b))

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
      seg.effect(s - 1, r, x);
    } else {
      ll i;
      cin >> i;
      cout << seg.get(i - 1) << '\n';
    }
  }
}
