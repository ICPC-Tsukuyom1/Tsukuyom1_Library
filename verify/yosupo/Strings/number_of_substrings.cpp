//@yosupo number_of_substrings

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Strings/SuffixArray.cpp"
void solve() {
  string s;
  in >> s;
  SuffixArray sa(s);
  ll sum = 0;
  rep(i, sz(sa.lcp)) sum += sa.lcp[i];
  ll n = sz(s);
  out << n * (n + 1) / 2 - sum << '\n';
}
int main() {
  ll T = 1;
  while (T--) solve();
}