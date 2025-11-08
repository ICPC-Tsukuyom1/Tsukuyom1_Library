//@yosupo staticrmq

#include "../../../template.cpp"

#define T int
#define op(a, b) min(a, b)

#include "../../../Structure/SparseTable.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  rep(i, n) { cin >> a[i]; }
  SparseTable st(a);
  rep(i, q) {
    int l, r;
    cin >> l >> r;
    cout << st.fold(l, r) << "\n";
  }
  return 0;
}
