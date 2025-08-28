//@yosupo point_add_range_sum

#include "../../../template.cpp"

#define T ll
#define e 0
#define op(a, b) a+b

#include "../../../Structure/segtree.cpp"

int main()
{
  ll n, q;
  cin >> n >> q;
  SegTree seg(n);
  rep(i, n)
  {
    ll a;
    cin >> a;
    seg.update(i, a);
  }
  while (q--)
  {
    ll t;
    cin >> t;
    if (t == 0)
    {
      ll p, x;
      cin >> p >> x;
      seg.update(p, seg.query(p, p + 1) + x);
    }
    else
    {
      ll l, r;
      cin >> l >> r;
      cout << seg.query(l, r) << '\n';
    }
  }
}
