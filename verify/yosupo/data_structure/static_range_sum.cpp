//@yosupo static_range_sum

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/BIT.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  vl a(n);
  rep(i, n) in >> a[i];
  BIT b(a);
  while (q--) {
    ll l, r;
    in >> l >> r;
    out << b.prod(l, r) << '\n';
  }
}
