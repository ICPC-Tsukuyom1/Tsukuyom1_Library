//@yosupo convolution_mod

#include "../../../template.cpp"
#include "../../../Math/convolution_mod.cpp"

int main() {
  ll N, M;
  cin >> N >> M;
  vec<ll> a(N), b(M);
  rep(i, N) cin >> a[i];
  rep(i, M) cin >> b[i];
  vl c = conv9(a, b);
  rep(i, sz(c)) { cout << c[i] << " \n"[i == sz(c) - 1]; }
}