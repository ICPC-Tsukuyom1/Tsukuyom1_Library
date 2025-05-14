Point getCrossPoint(Segment S1, Segment S2) {
    Point R = {1e9, 1e9};
    if (abs(ccw(S1.A,S1.B,S2.A)) != 1 && abs(ccw(S1.A,S1.B,S2.B)) != 1) return R;
    Vector base = S2.B - S2.A;
    ld d1 = abs(cross(base, S1.A - S2.A));
    ld d2 = abs(cross(base, S1.B - S2.A));
    ld T = d1 / (d1 + d2);
    return S1.A + (S1.B - S1.A) * T;
}
Point getCrossPoint(Point A, Point B, Point C, Point D) {
    Vector base = D - C;
    ld d1 = abs(cross(base, A - C));
    ld d2 = abs(cross(base, B - C));
    ld T = d1 / (d1 + d2);
    return A + (B - A) * T;
}
pair<Point, Point> getCrossPoints(Circle C, Line L) {
    assert(intersect(C, L));
    Vector pr = Projection(L, C.C);
    Vector e = (L.B - L.A) / (L.B - L.A).abs();
    ld base = sqrt(C.r * C.r - (pr - C.C).norm());
    return make_pair(pr + e * base, pr - e * base);
}
ld arg(Vector p) {return atan2(p.y, p.x);}
Vector polar(ld a, ld r) {return Point(cos(r) * a, sin(r) * a);}
pair<Point, Point> getCrossPoints(Circle c1, Circle c2) {
    assert(intersect(c1, c2)%4);
    ld d = (c1.C - c2.C).abs();
    ld a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    ld t = arg(c2.C - c1.C);
    return make_pair(c1.C + polar(c1.r, t + a), c1.C + polar(c1.r, t - a));
}
