//@yosupo zalgorithm

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Strings/ZAlgorithm.cpp"
void solve() {
  string s;
  in >> s;
  auto Z = Zalgo(s);
  rep(i, sz(s)) { out << Z[i] << " \n"[i + 1 == sz(s)]; }
}
int main() {
  ll T = 1;
  while (T--) solve();
}