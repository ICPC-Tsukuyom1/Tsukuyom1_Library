ld Area(Polygon S) {
    if (S.size() < 3) return 0;
    ld ans = 0;
    Point O = S[0];
    for (ll i = 1; i + 1 < S.size(); i++) {
        Point A = S[i], B = S[i+1];
        Vector C = A-O;
        Vector D = B-O;
        ld area = cross(C, D) * 0.5;
        ans += area;
    }
    return ans;
}
