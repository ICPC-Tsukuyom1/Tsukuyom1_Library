//@yosupo staticrmq

#include "../../../template.cpp"

#define T int
#define op(a, b) min(a, b)

#include "../../../Structure/disjoint-sparsetable.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  rep(i, n) { cin >> a[i]; }
  DisjointSparseTable dst(a);
  rep(i, q) {
    int l, r;
    cin >> l >> r;
    cout << dst.fold(l, r) << "\n";
  }
  return 0;
}
