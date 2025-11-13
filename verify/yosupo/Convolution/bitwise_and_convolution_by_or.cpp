//@yosupo bitwise_and_convolution

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/modint.cpp"
#include "../../../Math/bitwise_or_convolution.cpp"

int main() {
  int n;
  cin >> n;
  vec<mint> a(1 << n), b(1 << n);
  rep(i, 1 << n) cin >> a[i];
  rep(i, 1 << n) cin >> b[i];
  reverse(all(a));
  reverse(all(b));
  auto c = or_conv(a, b);
  reverse(all(c));
  rep(i, 1 << n) cout << c[i] << " \n"[i == (1 << n) - 1];
}