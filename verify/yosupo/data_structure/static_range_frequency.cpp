//@yosupo static_range_frequency

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
    int l, r;
    ll x;
    cin >> l >> r >> x;
    cout << wm(l, r).count(x) << '\n';
  }
}
