//@yosupo pow_of_matrix

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#include "../../../Math/matrix.cpp"

FastIn in;
FastOut out;

int main() {
  ll N, K;
  in >> N >> K;
  Matrix<mint> a(N, N);
  rep(i, N) rep(j, N) {
    ll temp;
    in >> temp;
    a[i][j] = mint(temp);
  }
  Matrix<mint> b = a ^ K;
  rep(i, N) rep(j, N) { out << b[i][j].x << " \n"[j == N - 1]; }
}