#include "commonTangents.cpp"
Point pol(double a,double r){ return Point(cosl(r)*a,sinl(r)*a); }
pair<Point, Point> ccInter(Circle c1, Circle c2) {
	if (sz(commonTangents(c1, c2)) % 4 == 0) {
		Point no = Point(-inf, -inf);
		return make_pair(no, no);
	}
	pair<Point, Point> ans;
	ld d = (c1.c - c2.c).abs();
	ld a = acosl((c1.r * c1.r + d * d - c2.r * c2.r) / (ld(2) * c1.r * d));
	ld t = (c2.c - c1.c).angle();
	ans.first = c1.c + pol(c1.r, t+a);
	ans.second = c1.c + pol(c1.r, t-a);
	if (!(ans.first < ans.second)) swap(ans.first, ans.second);
	return ans;
}