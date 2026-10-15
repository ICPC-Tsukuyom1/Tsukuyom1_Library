/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/math/convolution_mod.cpp */
//@yosupo convolution_mod

#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"

int main() {
  ll N, M;
  cin >> N >> M;
  FPS<ll> a(N), b(M);
  rep(i, N) cin >> a[i];
  rep(i, M) cin >> b[i];
  vl c = a * b;
  rep(i, sz(c)) { cout << c[i] << " \n"[i == sz(c) - 1]; }
}