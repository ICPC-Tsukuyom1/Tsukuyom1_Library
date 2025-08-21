//need : Point.cpp, ccw.cpp
bool isconvex(Polygon S) {
    ll n = sz(S);
    rep(i, n) {
        if (ccw(S[(i + n - 1) % n], S[i], S[(i + 1) % n]) == CLOCKWISE) return false;
    }
    return true;
}