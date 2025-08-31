#include "./Point.cpp"
// dist between a *line* and a point -> lineDistance.cpp
ld segDist(Segment S, Point p) {
	if (S.s == S.e) return (p-S.s).abs();
	auto d = (S.e - S.s).norm(), t = min(d, max(.0, (p - S.s).dot(S.e - S.s)));
	return ((p - S.s) * d - (S.e - S.s) * t).abs() / d;
}