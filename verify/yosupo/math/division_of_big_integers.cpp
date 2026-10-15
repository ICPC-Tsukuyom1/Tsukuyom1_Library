/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/verify/yosupo/math/division_of_big_integers.cpp */
//@yosupo division_of_big_integers

#include "../../../template.cpp"
#include "../../../Math/BigInt.cpp"


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll T;
  cin >> T;
  while (T--) {
    string a, b;
    cin >> a >> b;
    auto [q, r] = BigInt(a).divmod(BigInt(b));
    cout << q.to_string() << ' ' << r.to_string() << '\n';
  }
}
