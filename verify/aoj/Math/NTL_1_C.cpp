//@aoj NTL_1_C

#include "../../../template.cpp"
#include "../../../Math/extgcd.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  ll l = 1;
  rep(i, n) {
    ll a, x, y;
    cin >> a;
    ll g = extgcd(l, a, x, y);
    l = l / g * a;
  }
  cout << l << '\n';
}
