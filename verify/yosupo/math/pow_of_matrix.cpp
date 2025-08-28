//@yosupo pow_of_matrix

#include "../../../template.cpp"
const ll mod = 998244353;
#include "../../../Math/modint.cpp"
#include "../../../Math/matrix.cpp"

int main() {
    ll N, K; cin >> N >> K;
	Matrix<mint> a(N, N);
	rep(i, N) rep(j, N) cin >> a[i][j];
	Matrix<mint> b = a^K;
	rep(i, N) rep(j, N) {
		cout << b[i][j] << " \n"[j == N - 1];
	}
}