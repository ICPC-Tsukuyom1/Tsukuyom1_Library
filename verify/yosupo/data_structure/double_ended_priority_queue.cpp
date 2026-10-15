//@yosupo double_ended_priority_queue

#include "../../../template.cpp"
#include "../../../Structure/pbds.cpp"

int main() {
  ll n, q;
  cin >> n >> q;
  vl s(n);
  rep(i, n) cin >> s[i];
  MultiTree<ll> tree(all(s));
  while (q--) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll x;
      cin >> x;
      tree.insert(x);
    } else if (t == 1) {
      cout << *tree.begin() << '\n';
      tree.erase(tree.begin());
    } else if (t == 2) {
      auto itr = tree.end();
      cout << *--itr << '\n';
      tree.erase(itr);
    }
  }
}
