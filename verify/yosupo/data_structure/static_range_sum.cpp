//@yosupo static_range_sum

#include "../../../template.cpp"
#include "../../../Structure/BIT.cpp"

int main()
{
  ll n, q;
  cin >> n >> q;
  vl a(n);
  rep(i, n) cin >> a[i];
  BIT b(a);
  while (q--)
  {
    ll l, r;
    cin >> l >> r;
    cout << b.prod(l, r) << '\n';
  }
}
