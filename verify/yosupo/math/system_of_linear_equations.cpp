//@yosupo system_of_linear_equations

#include "../../../template.cpp"
#include "../../../Math/modint.cpp"
#include "../../../Math/matrix.cpp"
#include "../../../Math/solveLinear.cpp"
void solve() {
	ll n, m; cin >> n >> m;
  Matrix<mint> A(n, m);
  rep(i, n) rep(j, m) cin >> A[i][j];
  vec<mint> b(n); cin >> b;
  vec<mint> x;
  auto res = solveLinear(A, b);
  if (res.empty()) {
    cout << -1 << endl;
  } else {
    cout << sz(res) - 1 << endl;
    for (auto v : res) {
      cout << v;
    }
  }
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}