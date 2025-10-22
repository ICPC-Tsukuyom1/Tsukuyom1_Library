//@yosupo bitwise_xor_convolution

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/bitwise_xor_convolution.cpp"
#include "../../../Math/modint.cpp"

int main() {
  int n;
  cin >> n;
  vec<mint> a(1 << n), b(1 << n);
  rep(i, 1 << n) cin >> a[i];
  rep(i, 1 << n) cin >> b[i];
  auto c = xor_conv(a, b);
  rep(i, 1 << n) cout << c[i] << " \n"[i == (1 << n) - 1];
}