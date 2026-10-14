//@yosupo matrix_product

#include "../../../template.cpp"
#include "../../fastio.hpp"
const ll mod = 998244353;
#include "../../../Math/modint.cpp"
#include "../../../Math/matrix.cpp"

FastIn in;
FastOut out;

int main() {
  ll N, M, K;
  in >> N >> M >> K;
  Matrix<mint> a(N, M), b(M, K);
  rep(i, N) rep(j, M) {
    ll temp;
    in >> temp;
    a[i][j] = mint(temp);
  }
  rep(i, M) rep(j, K) {
    ll temp;
    in >> temp;
    b[i][j] = mint(temp);
  }
  Matrix<mint> c = a * b;
  rep(i, N) rep(j, K) { out << c[i][j].x << " \n"[j == K - 1]; }
}