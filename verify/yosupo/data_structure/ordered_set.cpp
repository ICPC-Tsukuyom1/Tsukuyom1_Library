//@yosupo ordered_set

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/pbds.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  vl a(n);
  rep(i, n) in >> a[i];
  Tree<ll> tree(all(a));
  rep(Q, q) {
    ll t, x;
    in >> t >> x;
    if (t == 0) {
      if (tree.find(x) == tree.end()) tree.insert(x);
    } else if (t == 1) {
      if (tree.find(x) != tree.end()) tree.erase(x);
    } else if (t == 2) {
      x--;
      if (tree.size() <= x) out << -1 << '\n';
      else out << *tree.find_by_order(x) << '\n';
    } else if (t == 3) {
      out << tree.order_of_key(x + 1) << '\n';
    } else if (t == 4) {
      auto itr = tree.upper_bound(x);
      if (itr == tree.begin()) out << -1 << '\n';
      else out << *--itr << '\n';
    } else {
      auto itr = tree.lower_bound(x);
      if (itr == tree.end()) out << -1 << '\n';
      else out << *itr << '\n';
    }
  }
}