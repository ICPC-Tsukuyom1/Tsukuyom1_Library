#include "./Point.cpp"
Point Projection(Segment S, Point p, bool reflect) {
    Vector base = S.e - S.s;
    ld r = (p - S.s).dot(base) / base.norm();
    if (reflect) {
        return p + (S.s + base * r - p) * 2.0;
    }
    else return S.s + base * r;
}