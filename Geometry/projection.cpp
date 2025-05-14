Point Projection(Segment S, Point p) {
    Vector base = S.B - S.A;
    ld r = dot(p - S.A, base) / base.norm();
    return S.A + base * r;
}
