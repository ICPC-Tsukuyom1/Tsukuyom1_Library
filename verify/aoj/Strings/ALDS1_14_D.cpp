//@aoj ALDS1_14_D

#include "../../../template.cpp"
#include "../../../Strings/SuffixArray.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string t, p;
  cin >> t;
  SuffixArray sa(t);
  ll q;
  cin >> q;
  while (q--) {
    cin >> p;
    ll len = sz(p);
    // first suffix in sa-order that is not less than p
    auto it = lower_bound(
        all(sa.sa), p,
        [&](const ll& idx, const string& pat) {
          return t.compare(idx, sz(pat), pat) < 0;
        });
    bool ok = it != sa.sa.end() && t.compare(*it, len, p) == 0;
    cout << (ok ? 1 : 0) << '\n';
  }
}
