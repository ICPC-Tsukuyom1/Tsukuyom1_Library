//@yosupo two_sat

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Graph/SCC.cpp"
#include "../../../Graph/twosat.cpp"

int main() {
  string _;
  ll N, M;
  in >> _ >> _ >> N >> M;
  Twosat ts(N);
  rep(i, M) {
    ll x, y, __;
    in >> x >> y >> __;
    bool f = (x > 0), g = (y > 0);
    ts.either(abs(x) - 1, f, abs(y) - 1, g);
  }
  auto ans = ts.satisfy();
  if (!sz(ans)) {
    out << "s "
         << "UNSATISFIABLE" << '\n';
    return 0;
  }
  out << "s "
       << "SATISFIABLE" << '\n';
  out << "v ";
  rep(i, N) { out << (i + 1) * ((ans[i]) ? 1 : -1) << " "; }
  out << 0 << '\n';
  return 0;
}