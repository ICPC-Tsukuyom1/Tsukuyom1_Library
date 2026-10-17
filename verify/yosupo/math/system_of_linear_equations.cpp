//@yosupo system_of_linear_equations

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modint.cpp"

using mint = modint<998244353>;

#include "../../../Math/matrix.cpp"
#include "../../../Math/solveLinear.cpp"

FastIn in;
FastOut out;

void solve() {
	ll n, m; in >> n >> m;
  Matrix<mint> A(n, m);
  rep(i, n) rep(j, m) {
    ll temp;
    in >> temp;
    A[i][j] = mint(temp);
  }
  vec<mint> b(n);
  rep(i, n) {
    ll temp;
    in >> temp;
    b[i] = mint(temp);
  }
  vec<mint> x;
  auto res = solveLinear(A, b);
  if (res.empty()) {
    out << -1 << '\n';
  } else {
    out << sz(res) - 1 << '\n';
    for (auto v : res) {
      rep(i, sz(v)) {
        out << v[i].x;
        if (i + 1 == sz(v)) out << '\n';
        else out << " ";
      }
    }
  }
}
int main() {
    ll T = 1;
    while (T--) solve();
}