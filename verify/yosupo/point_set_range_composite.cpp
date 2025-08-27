//@yosupo point_set_range_composite

#include "../../template.cpp"
#include "../../Math/modint.cpp"

using mint = modint<998244353>;

#include "../../Structure/segtree.cpp"


int main()
{
  ll n, q;
  cin >> n >> q;

  using T = pair<mint, mint>;
  SegTree<T> seg(
    n,
    [](T a, T b) { return T{a.first * b.first, a.second * b.first + b.second}; },
    T{1, 0}
  );
  rep(i, n)
  {
    mint a, b;
    cin >> a >> b;
    seg.update(i, {a, b});
  }
  while (q--)
  {
    ll t;
    cin >> t;
    if (t == 0)
    {
      ll p, c, d;
      cin >> p >> c >> d;
      seg.update(p, {c, d});
    }
    else
    {
      ll l, r, x;
      cin >> l >> r >> x;
      auto&& [a, b] = seg.query(l, r);
      cout << a * x + b << '\n';
    }
  }
}
