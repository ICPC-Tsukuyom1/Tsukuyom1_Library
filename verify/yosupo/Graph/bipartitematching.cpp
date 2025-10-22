//@yosupo bipartitematching

#include "../../../Graph/hopcroftKarp.cpp"
#include "../../../template.cpp"
void solve() {
  ll L, R, M;
  cin >> L >> R >> M;
  vv<ll> g(L + R);
  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    b += L;
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }
  vl btoa(L + R, -1);
  cout << hopcroftKarp(g, btoa) / 2 << endl;
  rep(i, L) {
    if (btoa[i] != -1) { cout << i << ' ' << btoa[i] - L << endl; }
  }
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}