//@yosupo inverse_matrix

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/matrix.cpp"
#include "../../../Math/modint.cpp"

int main() {
  ll N;
  cin >> N;
  Matrix<mint> a(N);
  rep(i, N) rep(j, N) cin >> a[i][j];
  if (a.det() == mint(0)) {
    cout << -1 << endl;
    return 0;
  }
  Matrix<mint> b = a.inv();
  rep(i, N) {
    rep(j, N) { cout << b[i][j] << " \n"[j == N - 1]; }
  }
}