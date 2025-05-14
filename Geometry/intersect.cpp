bool intersect(Point A, Point B, Point C, Point D) {
    return (ccw(A, B, C) * ccw(A, B, D) <= 0 && ccw(C, D, A) * ccw(C, D, B) <= 0);
}
bool intersect(Segment S1, Segment S2) {
    return intersect(S1.A, S1.B, S2.A, S2.B);
}
bool intersect(Circle C, Line L) {
    return (getDistance(L, C.C) <= C.r);
}
ll intersect(Circle C1, Circle C2) {
    ld d = (C1.C - C2.C).abs(), r1 = C1.r, r2 = C2.r;
    if (r1 + r2 < d) return 4;
    if (equals(r1 + r2, d)) return 3;
    if (equals(abs(r1-r2), d)) return 1;
    if (abs(r1-r2) > d) return 0;
    return 2;
}
