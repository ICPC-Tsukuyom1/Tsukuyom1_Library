#include "./Point.cpp"
// dist between a *segment* and a point -> segDistance.cpp
ld lineDist(Line L, Point p) {
    return (L.e - L.s).cross(p - L.s)/(L.e - L.s).abs();
}