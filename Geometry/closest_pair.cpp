ll ans = -1;
bool comp1(Point a, Point b) {return a.y < b.y;}
ld calc(Polygon &S, Polygon::iterator l, ll r) {
    if (r <= 1)return INF;
    ll m = r / 2;
    ld x = l[m].x;
    ld d = min(calc(S, l, m), calc(S, l+m, r-m));
    inplace_merge(l, l+m, l+r, comp1);
    Polygon vec;
    for (ll i = 0; i < r; i++) {
        if (fabs(l[i].x - x) >= d) continue;
        for (ll j = 0; j < vec.size(); j++) {
            ld dx = l[i].x - vec[vec.size()-j-1].x;
            ld dy = l[i].y - vec[vec.size()-j-1].y;
            if (dy >= d) break;
            if (d > sqrt(dx*dx+dy*dy)) {
                d = sqrt(dx*dx+dy*dy);
                ans = (ll)(dx*dx+dy*dy);
            }
        }
        vec.push_back(l[i]);
    }
    return d;
}
ld closest_pair(Polygon &S) {
    ll N = (ll)S.size();
    sort(S.begin(),S.end());
    return calc(S, S.begin(), N);
}
