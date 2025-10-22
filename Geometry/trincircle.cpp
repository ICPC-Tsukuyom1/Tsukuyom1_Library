#include "area.cpp"
Circle trinCircle(Polygon p) {
	assert(sz(p) == 3);
	vec<ld> a = { (p[1] - p[2]).abs(), (p[2] - p[0]).abs(), (p[0] - p[1]).abs() };
	ld sum = a[0] + a[1] + a[2];
	Point c;
	rep(i, 3) {
		c = c + p[i] * (a[i] / sum);
	}
	ld r = fabs(Area(p)) * (ld)2 / sum;
	return Circle(c, r);
}