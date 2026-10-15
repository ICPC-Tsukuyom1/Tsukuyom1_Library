/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/data_structure/static_range_sum_disjoint_sparsetable.cpp */
//@yosupo static_range_sum

#include "../../../template.cpp"

#define T ll
#define op(a, b) a + b

#include "../../../Structure/disjoint-sparsetable.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  vl a(n);
  rep(i, n) cin >> a[i];
  DisjointSparseTable dst(a);
  while (q--) {
    ll l, r;
    cin >> l >> r;
    cout << dst.fold(l, r) << '\n';
  }
}
