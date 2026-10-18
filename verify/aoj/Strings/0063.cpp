//@aoj 0063

#include "../../../template.cpp"
#include "../../../Strings/Manacher.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  ll ans = 0;
  while (cin >> s) {
    ll n = sz(s);
    auto p = Manacher(s);
    // the maximal palindrome centered at the middle must span the whole string
    // odd: length = 2 * p[1][i] + 1, even: length = 2 * p[0][i]
    if (n % 2 == 1) {
      if (p[1][n / 2] == n / 2) ans++;
    } else {
      if (p[0][n / 2] == n / 2) ans++;
    }
  }
  cout << ans << '\n';
}
