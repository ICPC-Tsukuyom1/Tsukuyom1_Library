bool isOrthogonal(Vector A, Vector B) {
    return equals(dot(A, B), 0.0);
}
bool isOrthogonal(Point A1, Point A2, Point B1, Point B2) {
    return isOrthogonal(A1 - A2, B1 - B2);
}
bool isOrthogonal(Segment S1, Segment S2) {
    return equals(dot(S1.B - S1.A, S2.B - S2.A), 0.0);
}
