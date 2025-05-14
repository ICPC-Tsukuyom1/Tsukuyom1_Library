bool isParallel(Vector A, Vector B) {
    return equals(cross(A, B), 0.0);
}
bool isParallel(Point A1, Point A2, Point B1, Point B2) {
    return isParallel(A1 - A2, B1 - B2);
}
bool isParallel(Segment S1, Segment S2) {
    return equals(cross(S1.B - S1.A, S2.B - S2.A), 0.0);
}
