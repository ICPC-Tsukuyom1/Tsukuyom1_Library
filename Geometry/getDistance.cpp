ld getDistance(Point A, Point B) {
    return (A - B).abs();
}
ld getDistance(Line L, Point P) {
    return abs((cross(L.B - L.A, P - L.A))) / (L.B - L.A).abs();
}
ld getDistance(Segment S, Point P) {
    if (dot(S.B - S.A, P - S.A) < 0.0) return (P - S.A).abs();
    if (dot(S.A - S.B, P - S.B) < 0.0) return (P - S.B).abs();
    return getDistance(S, P);
}
ld getDistance(Segment S1, Segment S2) {
    if (intersect(S1, S2)) return 0.0;
    return min(min(getDistance(S1, S2.A), getDistance(S1, S2.B)), min(getDistance(S2, S1.A), getDistance(S2, S1.B)));
}
