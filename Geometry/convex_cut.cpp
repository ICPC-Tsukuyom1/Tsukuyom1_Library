Polygon convex_cut(Polygon &G, Line& l) {
    Polygon res;
    ll N = (ll)G.size();
    for (ll i = 0; i < N; i++) {
        Point A = G[i], B = G[(i+1) % N];
        if (ccw(l.A, l.B, A) != -1) res.push_back(A);
        if (ccw(l.A,l.B, A) * ccw(l.A, l.B, B) < 0){
            Line L = {A, B};
            Point g = getCrossPoint(L, l);
            if (g.x == 1e9 && g.y == 1e9) continue;
            res.push_back(getCrossPoint(L, l));
        }
    }
    return res;
}
