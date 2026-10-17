//@yosupo matrix_det

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

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
  out << a.det().x << '\n';
}