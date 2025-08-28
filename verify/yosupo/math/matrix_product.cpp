//@yosupo matrix_product

#include "../../template.cpp"
const ll mod = 998244353;
#include "../../Math/modint.cpp"
#include "../../Math/matrix.cpp"

int main() {
    ll N, M, K; cin >> N >> M >> K;
    Matrix<mint> a(N, M), b(M, K);
    rep(i, N) rep(j, M) cin >> a[i][j];
    rep(i, M) rep(j, K) cin >> a[i][j];
    Matrix<mint> c = a * b;
    rep(i, N) rep(j, K) {
        cout << c[i][j] << " \n"[j == K - 1];
    }
}