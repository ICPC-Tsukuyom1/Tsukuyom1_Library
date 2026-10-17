//@yosupo suffixarray

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Strings/SuffixArray.cpp"

void solve() {
  string s;
  in >> s;
  SuffixArray sa(s);
  rep(i, sz(sa.sa) - 1) {
    out << sa.sa[i + 1] << " \n"[i + 1 == sz(sa.sa) - 1];
  }
}
int main() {
  ll T = 1;
  while (T--) solve();
}