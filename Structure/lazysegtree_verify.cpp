#include "../template.cpp"

const ll mod = 998244353;

#include "lazysegtree.cpp"

// Library Checker - Range Affine Range Sum
int main() {
  int n, q;
  cin >> n >> q;
  LazySeg *seg = new LazySeg(n);
  rep(i, n) {
    ll x;
    cin >> x;
    seg->effect(i, i+1, {0, x});
  }
  while (q--) {
    int type;
    cin >> type;
    if (type==0)
    {
      ll l, r, b, c;
      cin >> l >> r >> b >> c;
      seg->effect(l, r, {b, c});
    }
    else
    {
      int l, r;
      cin >> l >> r;
      cout << seg->query(l, r) << endl;
    }
  }
}