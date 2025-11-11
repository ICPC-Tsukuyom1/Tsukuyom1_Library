//@yosupo directedmst

#include "../../../template.cpp"
#include "../../../Structure/skew-heap.cpp"
#include "../../../Structure/UnionFind-rollback.cpp"
#include "../../../Graph/directed-mst.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m, s;
  cin >> n >> m >> s;
  vec<Edge> g;
  rep(i, m) {
    ll a, b, c;
    cin >> a >> b >> c;
    g.emplace_back(a, b, c);
  }
  auto [cost, par] = directed_mst(n, s, g);
  cout << cost << "\n";
  rep(i, n) {
    cout << (i == s ? s : par[i]) << " \n"[i == n-1];
  }
}