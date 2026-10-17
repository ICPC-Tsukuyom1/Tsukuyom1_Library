//@yosupo enumerate_palindromes

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Strings/Manacher.cpp"
void solve() {
  string s;
  in >> s;
  auto m = Manacher(s);
  rep(i, sz(s)) {
    out << m[1][i] * 2 + 1;
    if (i != sz(s) - 1) out << ' ' << m[0][i + 1] * 2 << ' ';
  }
  out << '\n';
}
int main() {
  ll T = 1;
  while (T--) solve();
}