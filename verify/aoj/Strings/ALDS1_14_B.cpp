//@aoj ALDS1_14_B

#include "../../../template.cpp"
#include "../../../Strings/KMP.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string t, p;
  cin >> t >> p;
  for (ll idx : match(t, p)) cout << idx << '\n';
}
