//@yosupo closest_pair

#include "../../../Geometry/closest_pair.cpp"

#include "../../../template.cpp"

void solve() {
  ll N;
  cin >> N;
  Polygon s(N);
  rep(i, N) { cin >> s[i].x >> s[i].y; }
  Polygon v = s;
  auto ans = closest(v);
  ll p = -1;
  rep(i, N) {
    if (s[i] == ans.first) { p = i; }
  }
  rep(i, N) {
    if (i == p) continue;
    if (s[i] == ans.second) {
      cout << p << ' ' << i << endl;
      return;
    }
  }
}
int main() {
  ll T = 1;
  cin >> T;
  while (T--) solve();
}