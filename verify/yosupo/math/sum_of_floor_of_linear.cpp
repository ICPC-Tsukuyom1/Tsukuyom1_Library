//@yosupo sum_of_floor_of_linear

#include "../../../template.cpp"
#include "../../../Math/floorsum.cpp"

void solve() {
  ll n, m, a, b;
  cin >> n >> m >> a >> b;
  cout << floorsum(n, a, b, m) << endl;
}
int main() {
  ll T = 1;
  cin >> T;
  while (T--) solve();
}