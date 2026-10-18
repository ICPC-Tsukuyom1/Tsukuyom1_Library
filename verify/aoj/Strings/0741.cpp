//@aoj 0741

#include "../../../template.cpp"
#include "../../../Strings/ZAlgorithm.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  string s;
  cin >> n >> s;
  vl z = Zalgo(s);
  // s is a repeating string (X + X) iff the suffix starting at n/2 equals the prefix
  cout << (z[n / 2] >= n / 2 ? "Yes" : "No") << '\n';
}
