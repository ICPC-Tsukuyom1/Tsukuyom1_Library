//@aoj 2614

#include "../../../template.cpp"
#include "../../../Strings/ZAlgorithm.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s, t;
  cin >> s >> t;
  ll n = sz(s), m = sz(t);
  // LCP of t and every suffix of s
  string a = t + '\0' + s;
  vl zl = Zalgo(a);
  // LCS (longest common suffix) of t and s[i, i+m) via reversed strings
  string rt(t.rbegin(), t.rend()), rs(s.rbegin(), s.rend());
  string b = rt + '\0' + rs;
  vl zr = Zalgo(b);
  ll ans = 0;
  rep(i, n - m + 1) {
    ll L = min(zl[m + 1 + i], m);
    ll R = min(zr[m + 1 + (n - i - m)], m);
    // prefix and suffix matches cover all but exactly one position
    if (L + R == m - 1) ans++;
  }
  cout << ans << '\n';
}
