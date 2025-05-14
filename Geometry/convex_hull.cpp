Polygon convex_hull(Polygon S) {
    Polygon u, l;
    if (S.size() < 3) return S;
    sort(S.begin(), S.end());
    ll k = 0;
    Polygon qs(S.size() * 2);
    rep(i, S.size()) {
        while (k > 1 && cross(qs[k - 1] - qs[k - 2], S[i] - qs[k - 1]) <= -EPS) k--;
        qs[k++] = S[i];
    }
    for (ll i = S.size() - 2, t = k; i >= 0; i--) {
        while (k > t && cross(qs[k - 1] - qs[k - 2], S[i] - qs[k - 1]) <= -EPS) k--;
        qs[k++] = S[i];
    }
    qs.resize(k - 1);
    return qs;
}