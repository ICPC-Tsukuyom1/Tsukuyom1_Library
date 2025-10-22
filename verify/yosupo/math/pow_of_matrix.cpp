//@yosupo pow_of_matrix

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/matrix.cpp"
#include "../../../Math/modint.cpp"

int main() {
  ll N, K;
  cin >> N >> K;
  Matrix<mint> a(N, N);
  rep(i, N) rep(j, N) cin >> a[i][j];
  Matrix<mint> b = a ^ K;
  rep(i, N) rep(j, N) { cout << b[i][j] << " \n"[j == N - 1]; }
}