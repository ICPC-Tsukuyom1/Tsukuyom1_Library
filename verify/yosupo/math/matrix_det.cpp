//@yosupo matrix_det

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/matrix.cpp"
#include "../../../Math/modint.cpp"

int main() {
  ll N;
  cin >> N;
  Matrix<mint> a(N);
  rep(i, N) rep(j, N) cin >> a[i][j];
  cout << a.det() << endl;
}