//@aoj DSL_5_B

#include "../../../template.cpp"
#include "../../../Structure/BIT2d.cpp"

// 1000×1000 の固定グリッドに長方形加算し、各セルの被覆枚数の最大値を求める。
// imos() で長方形加算(4 隅加点)し、セル (x, y) の値は [0, x] × [0, y] の累積和
// = 2 引数 sum(x + 1, y + 1) で取り出す。
int main() {
  ll n;
  cin >> n;
  BIT2d<ll> imos(1000, 1000);
  rep(i, n) {
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    imos.imos(x1, y1, x2, y2, 1);
  }
  ll ans = 0;
  for (ll x = 1; x <= 1000; x++) {
    for (ll y = 1; y <= 1000; y++) ans = max(ans, imos.sum(x, y));
  }
  cout << ans << endl;
}
