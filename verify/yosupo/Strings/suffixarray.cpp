//@yosupo suffixarray

#include "../../../template.cpp"
#include "../../../Strings/SuffixArray.cpp"

void solve() {
  string s;
  cin >> s;
  SuffixArray sa(s);
  rep(i, sz(sa.sa) - 1) {
    cout << sa.sa[i + 1] << " \n"[i + 1 == sz(sa.sa) - 1];
  }
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}