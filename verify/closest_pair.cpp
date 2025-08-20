// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/5/CGL_5_A

#include "../template.cpp"
#include "../Geometry/Point.cpp"
#include "../Geometry/closest_pair.cpp"

int main() {
    ll N; cin >> N;
    Polygon S(N);
    rep(i, N) cin >> S[i].x >> S[i].y;
    pair<Point, Point> ans = closest(S);
    cout << fixed << setprecision(12) << (ans.second - ans.first).abs() << endl;
}