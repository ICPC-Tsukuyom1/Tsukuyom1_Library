//@yosupo point_add_range_sum

#include "../../template.cpp"

#include "../../Structure/segtree.cpp"

int main()
{
  ll n, q;
  cin >> n >> q;
  SegTree<ll> seg(
    n,
    [](ll a, ll b) { return a + b; },
    0
  );
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
