//@yosupo unionfind

#include "../../../template.cpp"
#include "../../../Structure/unionfind.cpp"

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
      cout << (uf.root(u) == uf.root(v)) << endl;
    }
  }
}