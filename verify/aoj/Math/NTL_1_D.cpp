//@aoj NTL_1_D

#include "../../../template.cpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/MillerRabin.cpp"
#include "../../../Math/FastFactorize.cpp"
#include "../../../Math/Euler_phi.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  cout << Euler_phi(n) << '\n';
}
