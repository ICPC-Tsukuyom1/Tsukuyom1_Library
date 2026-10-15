//@yosupo system_of_linear_equations

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/modint.cpp"
#include "../../../Math/matrix.cpp"
#include "../../../Math/solveLinear.cpp"
void solve() {
	ll n, m; cin >> n >> m;
  Matrix<mint> A(n, m);
  rep(i, n) rep(j, m) cin >> A[i][j];
  vec<mint> b(n);
  rep(i, n) cin >> b[i];
  vec<mint> x;
  auto res = solveLinear(A, b);
  if (res.empty()) {
    cout << -1 << endl;
  } else {
    cout << sz(res) - 1 << endl;
    for (auto v : res) {
      rep(i, sz(v)) {
        cout << v[i];
        if (i + 1 == sz(v)) cout << endl;
        else cout << " ";
      }
    }
  }
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}