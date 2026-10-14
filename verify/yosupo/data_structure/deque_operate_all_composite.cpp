//@yosupo deque_operate_all_composite

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

using T = pair<mint, mint>;
const T e = pair{1, 0};
#define op(a, b) \
  pair { a.first *b.first, b.first *a.second + b.second }

#include "../../../Structure/swag.cpp"

int main() {

  ll q;
  in >> q;
  SWAG s;
  while (q--) {
    ll t;
    in >> t;
    if (t == 0) {
      ll a, b;
      in >> a >> b;
      s.push_front({a, b});
    } else if (t == 1) {
      ll a, b;
      in >> a >> b;
      s.push_back({a, b});
    } else if (t == 2) {
      s.pop_front();
    } else if (t == 3) {
      s.pop_back();
    } else {
      ll x;
      in >> x;
      auto a = s.query();
      out << (a.first * x + a.second).x << "\n";
    }
  }
}