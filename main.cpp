#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using vl = vector<ll>;
#define rep(i, r) for(ll i = 0; i < (r); i++)
#define reps(i, l, r) for(ll i = (l); i < (r); i++)
#define rrep(i, r, l) for(ll i = (r) - 1; i >= l; i--)
#define all(a) (a).begin(), (a).end()
#define sz(a) (ll)(a).size()
template <typename T>
bool chmax(T &a, const T& b) { return a < b ? a = b, true : false; }
template <typename T>
bool chmin(T &a, const T& b) { return a > b ? a = b, true : false; }
#define EPS (1e-10)
#define eq(a, b) (fabs((a) - (b)) < EPS)
class Point {
	typedef Point P;
public:
    ld x, y;

    Point(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}

    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(ld a) const { return P(a * x, a * y); }
    P operator/(ld a) const { return P(x / a, y / a); }

    ld abs() { return sqrtl(norm()); }
    ld norm() { return x * x + y * y; }

    bool operator<(const P& p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(const P& p) const { return eq(x, p.x) && eq(y, p.y); }
	ld dot(P p) const { return x * p.x + y * p.y; }
	ld cross(P p) const { return x * p.y - y * p.x; }

};
typedef Point Vector;
struct Segment {
    Point A;
    Point B;
};
typedef Segment Line;
class Circle {
public:
    Point C;
    ld r;
    Circle(Point C = Point(), ld r = 0.0) : C(C), r(r) {}
};
typedef vector<Point> Polygon;
#define P Point
pair<P, P> closest (Polygon &v) {
    set<P> s;
    sort(all(v), [](P a, P b){ return a.y < b.y; });
    pair<ld, pair<P, P>> ans = {LDBL_MAX, {P(), P()}};
    ll j = 0;
    for (P p: v) {
        P d{ans.first, 0};
        while (v[j].y <= p.y - d.x) s.erase(v[j++]);
        auto lo = s.lower_bound(p - d), hi = s.upper_bound(p + d);
        for (; lo != hi; lo = ++lo) chmin(ans, {(*lo - p).abs(), {*lo, p}});
        s.insert(p);
    }
    return ans.second;
}
#undef P
int main() {
    ll N; cin >> N;
    Polygon S(N);
    rep(i, N) cin >> S[i].x >> S[i].y;
    pair<Point, Point> ans = closest(S);
    cout << fixed << setprecision(12) << (ans.second - ans.first).abs() << endl;
}