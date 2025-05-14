Point Reflection(Segment S, Point p) {
    return p + (Projection(S, p) - p) * 2.0;
}
