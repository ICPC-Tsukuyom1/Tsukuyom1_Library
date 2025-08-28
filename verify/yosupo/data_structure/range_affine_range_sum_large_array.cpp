//@yosupo range_affine_range_sum_large_array

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

#define T mint
#define e 0
#define F pair<mint, mint>
#define id F{1, 0}
#define op(a, b) a+b
#define merge(a, b) F{a.first * b.first, a.second * b.first + b.second}
#define apply(f, x, l) f.first * x + f.second * l

#include "../../../Structure/lazysegtree.cpp"

int main()
{
  ll n, q;
  cin >> n >> q;
  auto* seg = new LazySeg(n);
  while (q--)
  {
    int type;
    cin >> type;
    if (type == 0)
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
