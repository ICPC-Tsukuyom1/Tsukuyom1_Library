/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/math/primroot.cpp */
//@yosupo primitive_root

#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/MillerRabin.cpp"
#include "../../../Math/FastFactorize.cpp"
#include "../../../Math/primroot.cpp"

void solve() {
  ll n;
  cin >> n;
  cout << primroot(n) << endl;
}
int main() {
  ll T = 1;
  cin >> T;
  while (T--) solve();
}