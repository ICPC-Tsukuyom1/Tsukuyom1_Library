// depends on: Point
// strict = true => NOT include points on edge
// strict = false => include points on edge
Polygon convex_hull(Polygon &p, bool str = 1) {
  sort(all(p));
  p.erase(unique(all(p)), p.end());
  ll n = sz(p), k = 0;
  if (n <= 2) return p;
  vec<Point> c(2*n);
  auto check = [&](ll i) {
    Point a = c[k-1] - c[k-2], b = p[i] - c[k-1];
    return a.cross(b) <= (str ? EPS : -EPS);
  };
  for (ll i = 0; i < n; c[k++] = p[i++])
    while (k >= 2 && check(i)) --k;
  for (ll i = n-2, t = k+1; i>=0; c[k++] = p[i--])
    while (k >= t && check(i)) --k;
  c.resize(k-1);
  return c;
}