//@yosupo unionfind_with_potential

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"
#include "../../../Structure/weightedunionfind.cpp"

int main() {
  ll n, q;
  cin >> n >> q;
  WeightedUnionFind<mint> uf(n);
  while (q--) {
    ll t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      mint x;
      cin >> x;
      if (uf.find(u) == uf.find(v)) {
        if (uf.weight(u) - uf.weight(v) != x) {
          cout << 0 << endl;
          continue;
        }
      }
      uf.merge(v, u, x);
      cout << 1 << endl;
    } else {
      if (uf.find(u) == uf.find(v)) {
        cout << uf.weight(u) - uf.weight(v) << endl;
      } else {
        cout << -1 << endl;
      }
    }
  }
}