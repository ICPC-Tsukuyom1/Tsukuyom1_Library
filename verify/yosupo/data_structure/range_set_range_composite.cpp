//@yosupo range_set_range_composite

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

#define T pair<mint, mint>
#define e \
  T { 1, 0 }
#define F pair<mint, mint>
#define id \
  F { 0, 0 }
#define op(a, b) \
  T { a.first *b.first, a.second *b.first + b.second }

T pow_fn(T fn, ll n) {
  T ans = e;
  while (n > 0) {
    if (n & 1) ans = op(ans, fn);
    fn = op(fn, fn);
    n >>= 1;
  }
  return ans;
}

#define merge(a, b) b.first == 0 ? a : b
#define apply(f, x, l) f.first == 0 ? x : pow_fn(f, l)

#include "../../../Structure/lazysegtree.cpp"

int main() {
  int n, q;
  cin >> n >> q;
  auto* seg = new LazySeg(n);
  rep(i, n) {
    ll a, b;
    cin >> a >> b;
    seg->effect(i, i + 1, {a, b});
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      ll l, r, c, d;
      cin >> l >> r >> c >> d;
      seg->effect(l, r, {c, d});
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      auto [a, b] = seg->query(l, r);
      cout << a * x + b << endl;
    }
  }
}
