// need: Point.cpp
ld lineDist(Line L, Point p) {
    return (L.B - L.A).cross(p - L.A)/(L.B - L.A).abs();
}