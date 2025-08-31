ld getDistance(Segment S1, Segment S2) {
    if (intersect(S1, S2)) return 0.0;
    return min(min(getDistance(S1, S2.A), getDistance(S1, S2.B)), min(getDistance(S2, S1.A), getDistance(S2, S1.B)));
}
