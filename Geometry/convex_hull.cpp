// need: Point.cpp
// strict = true => NOT include points on edge
// strict = false => include points on edge
Polygon convex_hull(Polygon &p, bool strict = true) {
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    ll n = sz(p), k = 0;
    if (n <= 2) return p;
    vector<Point> ch(2 * n);
    auto check = [&](ll i) {
        Point a = ch[k - 1] - ch[k - 2], b = p[i] - ch[k - 1];
        if (strict) {
            return a.cross(b) <= EPS;
        }
        else {
            return a.cross(b) <= -EPS;
        }
    };
    for (ll i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && check(i)) --k;
    }
    for (ll i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && check(i)) --k;
    }
    ch.resize(k - 1);
    return ch;
}