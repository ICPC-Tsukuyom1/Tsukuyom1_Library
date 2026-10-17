//@yosupo set_xor_min

#include "../../../template.cpp"

#include "../../../Structure/binary-trie.cpp"

using Trie =
    BinaryTrie<ll, [](ll a, ll b) { return a + b; }, []() { return 0LL; }, 30>;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  Trie trie;
  ll q;
  cin >> q;
  rep(Q, q) {
    ll t;
    ll x;
    cin >> t >> x;
    if (t == 0) {
      if (trie.get(x) == 0) trie.insert(x, 1);
    } else if (t == 1) {
      trie.erase(x);
    } else {
      trie.xor_all(x);
      cout << trie.at(0) << '\n';
      trie.xor_all(x);
    }
  }
}
