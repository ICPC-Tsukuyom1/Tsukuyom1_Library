#include "Point.cpp"
const ld pi = 3.141592653589793238;
ld fac(Circle c1, Circle c2) {
	ld dd = (c2.c - c1.c).norm();
	if (sign(dd - (c1.r + c2.r) * (c1.r + c2.r)) >= 0) return 0.0;
	if (sign((c1.r - c2.r) * (c1.r - c2.r) - dd) >= 0) return pi*min(c1.r, c2.r)*min(c1.r, c2.r);
	ld p1 = (c1.r * c1.r - c2.r * c2.r + dd), p2 = (c2.r * c2.r - c1.r * c1.r + dd);
	ld s1 = (c1.r * c1.r) * atan2(sqrtl(ld(4) * dd * c1.r * c1.r - p1 * p1), p1);
	ld s2 = (c2.r * c2.r) * atan2(sqrtl(ld(4) * dd * c2.r * c2.r - p2 * p2), p2);
	ld s0 = sqrtl(4 * dd * c1.r * c1.r - p1 * p1) / ld(2);
	return s1 + s2 - s0;
}