//@aoj DSL_5_B

#include "../../../template.cpp"
#include "../../../Structure/BIT2d.cpp"

// 1000×1000 の固定グリッドに長方形加算し、各セルの被覆枚数の最大値を求める。
// imos() は 4 隅加点で半開区間 [x1, x2) × [y1, y2) を加算し、セル (i, j) の値は
// 2 引数 sum(i + 1, j + 1) で取れる。下のループの sum(x, y) はセル (x - 1, y - 1) を読む。
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
