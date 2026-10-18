//@aoj NTL_1_B

#include "../../../template.cpp"
#include "../../../Math/modint.cpp"

using mint = modint<1000000007>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll m, n;
  cin >> m >> n;
  cout << mint(m).pow(n) << '\n';
}
