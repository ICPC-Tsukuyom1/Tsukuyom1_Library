// need: Point.cpp
// dist between a *line* and a point -> lineDistance.cpp
ld segDist(Segment S, Point p) {
	if (S.A == S.B) return (p-S.A).abs();
	auto d = (S.B - S.A).norm(), t = min(d, max(.0, (p - S.A).dot(S.B - S.A));
	return ((p - S.A) * d - (S.B - S.A) * t).abs() / d;
}