//@yosupo double_ended_priority_queue

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/pbds.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  vl s(n);
  rep(i, n) in >> s[i];
  MultiTree<ll> tree(all(s));
  while (q--) {
    ll t;
    in >> t;
    if (t == 0) {
      ll x;
      in >> x;
      tree.insert(x);
    } else if (t == 1) {
      out << *tree.begin() << '\n';
      tree.erase(tree.begin());
    } else if (t == 2) {
      auto itr = tree.end();
      out << *--itr << '\n';
      tree.erase(itr);
    }
  }
}
