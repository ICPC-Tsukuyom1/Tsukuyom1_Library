/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/Strings/zalgorithm.cpp */
//@yosupo zalgorithm

#include "../../../template.cpp"
#include "../../../Strings/ZAlgorithm.cpp"
void solve() {
  string s;
  cin >> s;
  auto Z = Zalgo(s);
  rep(i, sz(s)) { cout << Z[i] << " \n"[i + 1 == sz(s)]; }
}
int main() {
  ll T = 1;
  // cin >> T;
  while (T--) solve();
}