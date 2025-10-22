//@yosupo unionfind

#include "../../../Structure/unionfind.cpp"

#include "../../../template.cpp"

int main() {
  ll n, q;
  cin >> n >> q;
  UnionFind uf(n);
  while (q--) {
    ll t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      uf.unite(u, v);
    } else {
      cout << (int)uf.same(u, v) << endl;
    }
  }
}