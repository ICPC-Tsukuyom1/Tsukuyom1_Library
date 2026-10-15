/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/Strings/number_of_substrings.cpp */
//@yosupo number_of_substrings

#include "../../../template.cpp"
#include "../../../Strings/SuffixArray.cpp"
void solve() {
  string s;
  cin >> s;
  SuffixArray sa(s);
  ll sum = 0;
  rep(i, sz(sa.lcp)) sum += sa.lcp[i];
  ll n = sz(s);
  cout << n * (n + 1) / 2 - sum << endl;
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}