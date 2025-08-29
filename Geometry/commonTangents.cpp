#include "./Point.cpp"
vec<Line> commonTangents(Circle c1, Circle c2) {
	bool s = false;
	if (c1.r < c2.r) {
		s = true;
		swap(c1, c2);
	}
	typedef Point P;
	ld d = (c1.c - c2.c).abs();
	vec<Line> L;
	if (c1.r - c2.r <= d + EPS) {
		if (c1.r - c2.r <= EPS) {
			P D = (c2.c - c1.c).perp() / d * c1.r;
			L.push_back(Line(c1.c + D, c2.c + D));
			L.push_back(Line(c1.c - D, c2.c - D));
		} else {
			ld m = (c1.r - c2.r) * (c1.r - c2.r) / d;
			P M = c1.c + (c2.c - c1.c) / d * m;
			ld h = sqrtl((c1.r - c2.r) * (c1.r - c2.r) - m * m);
			P H1 = M + (c2.c - c1.c).normal() * h;
			P D1 = (H1 - c1.c).unit() * c2.r;
			L.push_back(Line(H1 + D1, c2.c + D1));
			P H2 = M - (c2.c - c1.c).normal() * h;
			P D2 = (H2 - c1.c).unit() * c2.r;
			L.push_back(Line(H2 + D2, c2.c + D2));
		}
	}
	if (c1.r + c2.r <= d + EPS) {
		ld m = (c1.r + c2.r) * (c1.r + c2.r) / d;
		P M = c1.c + (c2.c - c1.c).unit() * m;
		ld h = sqrtl((c1.r + c2.r) * (c1.r + c2.r) - m * m);
		P H1 = M + (c2.c - c1.c).normal() * h;
		P D1 = (H1 - c1.c).unit() * c2.r;
		L.push_back(Line(H1 - D1, c2.c - D1));
		P H2 = M - (c2.c - c1.c).normal() * h;
		P D2 = (H2 - c1.c).unit() * c2.r;
		L.push_back(Line(H2 - D2, c2.c - D2));
	}
	if (s) {
		rep(i, sz(L)) swap(L[i].s, L[i].e);
	}
	return L;
}