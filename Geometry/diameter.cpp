bool cmp(Point Q1, Point Q2) {
    if (Q1.x != Q2.x) return Q1.x < Q2.x;
    return Q1.y < Q2.y;
}
ld DiameterPolygon(Polygon S) {
    Polygon Q = convex_hull(S);
    ll N = Q.size();
    if (N == 2) {
        return getDistance(Q[0], Q[1]);
    }
    ll i = 0, j = 0;
    for (ll k = 0; k < N; k++) {
        if (!cmp(Q[i], Q[k])) i = k;
        if (cmp(Q[j], Q[k])) j = k; 
    }
    ld res = (Q[i] - Q[j]).norm();
    ll si = i, sj = j;
    ll maxi = si, maxj = sj;
    do {
        if (cross(Q[(i+1)%N]-Q[i], Q[(j+1)%N] - Q[j]) >= 0) {
            j = (j+1) % N;
        }
        else {
            i = (i+1) % N;
        }
        if ((Q[i] - Q[j]).norm() > res) {
            res = (Q[i] - Q[j]).norm();
            maxi = i;
            maxj = j;
        }
    } while (i != si || j != sj);
    return sqrt(res);
}
