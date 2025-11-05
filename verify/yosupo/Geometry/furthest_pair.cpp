//@yosupo furthest_pair

#include "../../../template.cpp"
#include "../../../Geometry/diamConvex.cpp"
void solve() {
  ll n;
  cin >> n;
  Polygon g(n);
  rep(i, n) cin >> g[i].x >> g[i].y;
  auto res = diamConvex(g);
  ll l, r;
  rep(i, n) if (res.first == g[i]) {
    l = i;
    break;
  }
  rep(i, n) if (res.second == g[i] && l != i) {
    r = i;
    break;
  }
  cout << l << ' ' << r << endl;
}
int main() {
  ll T = 1;
  cin >> T;
  while (T--) solve();
}