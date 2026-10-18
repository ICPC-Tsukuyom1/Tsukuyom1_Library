//@aoj GRL_7_A

#include "../../../template.cpp"
#include "../../../Graph/hopcroftKarp.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll X, Y, E;
  cin >> X >> Y >> E;
  vv<ll> g(X);
  rep(i, E) {
    ll x, y;
    cin >> x >> y;
    g[x].push_back(y);
  }
  vl btoa(Y, -1);
  cout << hopcroftKarp(g, btoa) << '\n';
}
