//@yosupo multiplication_of_big_integers

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
    cout << (BigInt(a) * BigInt(b)).to_string() << '\n';
  }
}
