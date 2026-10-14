//@yosupo associative_array

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/pbds.cpp"

using ull = unsigned long long;

struct chash {
  ull operator()(ll X) const {
    ull x = X;
    x ^= rotr(x, 23) ^ rotr(x, 47);
    x ^= x >> 13;
    x ^= x << 37;
    x ^= x >> 21;
    return x;
  }
};

int main() {
  ll q;
  in >> q;
  FastMap<ll, ll, chash> mp;
  rep(Q, q) {
    ll t;
    in >> t;
    if (t == 0) {
      ll k, v;
      in >> k >> v;
      mp[k] = v;
    } else {
      ll k;
      in >> k;
      out << (mp.find(k) == mp.end() ? 0 : mp[k]) << "\n";
    }
  }
}