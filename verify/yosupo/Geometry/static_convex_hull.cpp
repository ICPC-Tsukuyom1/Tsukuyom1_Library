//@yosupo static_convex_hull

#include "../../../template.cpp"
#include "../../../Geometry/Point.cpp"
#include "../../../Geometry/convex_hull.cpp"
int main() {
  ll T;
  cin >> T;
  while (T--) {
    ll N;
    cin >> N;
    Polygon S(N);
    rep(i, N) cin >> S[i].x >> S[i].y;
    Polygon ans = convex_hull(S);
    cout << sz(ans) << endl;
    rep(i, sz(ans)) { cout << (ll)ans[i].x << ' ' << (ll)ans[i].y << endl; }
  }
}