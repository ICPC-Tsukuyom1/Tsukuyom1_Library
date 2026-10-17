//@yosupo ordered_set

#include "../../../template.cpp"

#include "../../../Structure/binary-trie.cpp"

using Trie =
    BinaryTrie<ll, [](ll a, ll b) { return a + b; }, []() { return 0LL; }, 30>;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  Trie trie;
  ll n, q;
  cin >> n >> q;
  rep(i, n) {
    ll x;
    cin >> x;
    if (trie.get(x) == 0) trie.insert(x, 1);
  }
  rep(Q, q) {
    ll t;
    ll x;
    cin >> t >> x;
    if (t == 0) {
      if (trie.get(x) == 0) trie.insert(x, 1);
    } else if (t == 1) {
      trie.erase(x);
    } else if (t == 2) {
      if (x == 0 || x > trie.size()) {
        cout << -1 << '\n';
      } else {
        cout << trie.at(x - 1) << '\n';
      }
    } else if (t == 3) {
      cout << trie.query(0, x + 1) << '\n';
    } else if (t == 4) {
      ll count = trie.query(0, x + 1);
      if (count == 0) cout << -1 << '\n';
      else cout << trie.at(count - 1) << '\n';
    } else {
      ll count = trie.query(0, x);
      if (count == trie.size()) cout << -1 << '\n';
      else cout << trie.at(count) << '\n';
    }
  }
}
