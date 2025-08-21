//need: Point.cpp
bool onSegment(Segment S, Point p) {
	return p.cross(S.s, S.e) == 0 && (S.s - p).dot(S.e - p) <= 0;
}