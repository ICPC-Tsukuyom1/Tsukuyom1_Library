// need: Point.cpp
ld Area(Polygon S) {
    ld ans = 0;
    rep(i, sz(S) - 2) {
        Point a = S[i + 1] - S[0], b = S[i + 2] - S[0];
        ans += a.cross(b) * 0.5;
    }
    return ans;
}