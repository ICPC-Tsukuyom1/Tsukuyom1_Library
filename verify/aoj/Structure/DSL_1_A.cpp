//@aoj DSL_1_A

#include "../../../template.cpp"
#include "../../../Structure/unionfind.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  UnionFind uf(n);
  while (q--) {
    ll com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      uf.unite(x, y);
    } else {
      cout << (uf.root(x) == uf.root(y)) << '\n';
    }
  }
}
