//@yosupo number_of_substrings

#include "../../../Strings/SuffixArray.cpp"
#include "../../../template.cpp"
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