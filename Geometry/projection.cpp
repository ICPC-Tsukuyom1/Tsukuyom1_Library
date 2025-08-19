Point Projection(Segment S, Point p, bool reflect) {
    Vector base = S.B - S.A;
    ld r = (p - S.A).dot(base) / base.norm();
    if (reflect) {
        return p + (S.A + base * r - p) * 2.0;
    }
    else return S.A + base * r;
}