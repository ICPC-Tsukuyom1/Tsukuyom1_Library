//@yosupo inverse_matrix

#include "../../../template.cpp"
#include "../../fastio.hpp"
const ll mod = 998244353;
#include "../../../Math/modint.cpp"
#include "../../../Math/matrix.cpp"

FastIn in;
FastOut out;

int main() {
  ll N;
  in >> N;
  Matrix<mint> a(N);
  rep(i, N) rep(j, N) {
    ll temp;
    in >> temp;
    a[i][j] = mint(temp);
  }
  if (a.det() == mint(0)) {
    out << -1 << '\n';
    return 0;
  }
  Matrix<mint> b = a.inv();
  rep(i, N) {
    rep(j, N) { out << b[i][j].x << " \n"[j == N - 1]; }
  }
}