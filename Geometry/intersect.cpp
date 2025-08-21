bool intersect(Point A, Point B, Point C, Point D) {
    return (ccw(A, B, C) * ccw(A, B, D) <= 0 && ccw(C, D, A) * ccw(C, D, B) <= 0);
}
bool intersect(Segment S1, Segment S2) {
    return intersect(S1.A, S1.B, S2.A, S2.B);
}