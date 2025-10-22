//@yosupo ordered_set

#include "../../../Structure/pbds.cpp"
#include "../../../template.cpp"

int main() {
  ll n, q;
  cin >> n >> q;
  vl a(n);
  rep(i, n) cin >> a[i];
  Tree<ll> tree(all(a));
  rep(Q, q) {
    ll t, x;
    cin >> t >> x;
    if (t == 0) {
      if (tree.find(x) == tree.end()) tree.insert(x);
    } else if (t == 1) {
      if (tree.find(x) != tree.end()) tree.erase(x);
    } else if (t == 2) {
      x--;
      if (tree.size() <= x) cout << -1 << '\n';
      else cout << *tree.find_by_order(x) << '\n';
    } else if (t == 3) {
      cout << tree.order_of_key(x + 1) << '\n';
    } else if (t == 4) {
      auto itr = tree.upper_bound(x);
      if (itr == tree.begin()) cout << -1 << '\n';
      else cout << *--itr << '\n';
    } else {
      auto itr = tree.lower_bound(x);
      if (itr == tree.end()) cout << -1 << '\n';
      else cout << *itr << '\n';
    }
  }
}