//@aoj DSL_2_H

#include "../../../template.cpp"

#define T ll
#define e 4000000000000000000LL
#define op(a, b) min(a, b)
#define F ll
#define id 0LL
#define merge(a, b) ((a) + (b))
#define apply(f, x, len) ((x) + (f))

#include "../../../Structure/lazysegtree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  LazySeg seg(n);
  // 初期値はすべて 0。LazySeg は全要素を e (min の単位元) で初期化するので，
  // 実要素にあたる葉を 0 に直して内部ノードを再計算しておく。
  rep(i, n) seg.v[seg.n + i] = 0;
  rrep(i, 1, seg.n) seg.v[i] = op(seg.v[i * 2], seg.v[i * 2 + 1]);
  while (q--) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll s, r, x;
      cin >> s >> r >> x;
      seg.effect(s, r + 1, x);
    } else {
      ll s, r;
      cin >> s >> r;
      cout << seg.query(s, r + 1) << '\n';
    }
  }
}
