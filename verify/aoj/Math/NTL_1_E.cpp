//@aoj NTL_1_E

#include "../../../template.cpp"
#include "../../../Math/extgcd.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll a, b;
  cin >> a >> b;
  ll x, y;
  extgcd(a, b, x, y);
  cout << x << ' ' << y << '\n';
}
