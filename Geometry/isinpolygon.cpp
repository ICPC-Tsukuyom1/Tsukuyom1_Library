int isinpolygon(Point p, Polygon S) {
    ll N = (ll)S.size();
    bool check = false;
    for (ll i = 0; i < N; i++) {
        Point A = S[i] - p, B = S[(i+1)%N] - p;
        if (abs(cross(A, B)) < EPS && dot(A, B) < EPS) return 1;
        if (A.y > B.y) swap(A, B);
        if (A.y < EPS && EPS < B.y && cross(A, B) > EPS) check = !check;
    }
    return (check ? 2 : 0);
}
