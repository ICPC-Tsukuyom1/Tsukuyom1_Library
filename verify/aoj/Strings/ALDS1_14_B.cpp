//@aoj ALDS1_14_B

#include "../../../template.cpp"
#include "../../../Structure/RollingHash.cpp"

int main() {
  string s, p;
  cin >> s >> p;
  RollingHash rs(s), rp(p);
  ll m = p.size();
  for (ll i = 0; i + m <= (ll)s.size(); i++) {
    if (rs.get(i, i + m) == rp.get(0, m)) cout << i << "\n";
  }
}
