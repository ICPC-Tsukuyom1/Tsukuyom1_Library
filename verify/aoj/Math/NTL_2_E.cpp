//@aoj NTL_2_E

#include "../../../template.cpp"
#include "../../../Math/BigInt.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string a, b;
  cin >> a >> b;
  cout << (BigInt(a) % BigInt(b)).to_string() << '\n';
}
