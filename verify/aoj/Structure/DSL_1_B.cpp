//@aoj DSL_1_B

#include "../../../template.cpp"
#include "../../../Structure/weightedunionfind.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  WeightedUnionFind<ll> uf(n);
  while (q--) {
    ll t, x, y;
    cin >> t >> x >> y;
    if (t == 0) {
      ll z;
      cin >> z;
      // a_y - a_x = z
      uf.merge(x, y, z);
    } else if (uf.find(x) == uf.find(y)) {
      cout << uf.weight(y) - uf.weight(x) << '\n';
    } else {
      cout << "?\n";
    }
  }
}
