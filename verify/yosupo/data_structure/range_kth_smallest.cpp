//@yosupo range_kth_smallest

#include "../../../template.cpp"
#include "../../../Structure/wavelet-matrix.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vl a(n);
  for (auto& x : a) cin >> x;
  const WaveletMatrix<> wm(a);
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << wm(l, r).kth_smallest(k) << '\n';
  }
}
