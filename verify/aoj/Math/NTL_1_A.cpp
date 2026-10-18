//@aoj NTL_1_A

#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/MillerRabin.cpp"
#include "../../../Math/FastFactorize.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  vl p = fac(n);
  sort(all(p));
  cout << n << ':';
  for (ll x : p) cout << ' ' << x;
  cout << '\n';
}
