/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Geometry/Point3D.cpp */
struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  ld x, y, z;
  explicit Point3D(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
  bool operator<(R p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(R p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
  P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
  P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
  P operator*(ld d) const { return P(x * d, y * d, z * d); }
  P operator/(ld d) const { return P(x / d, y / d, z / d); }
  ld dot(R p) const { return x * p.x + y * p.y + z * p.z; }
  P cross(R p) const {
    return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
  }
  ld norm() const { return x * x + y * y + z * z; }
  ld abs() const { return sqrtl(norm()); }
  ld phi() const { return atan2l(y, x); }
  ld theta() const { return atan2l(sqrtl(x * x + y * y), z); }
  P unit() const { ld a = abs(); return a ? P(x / a, y / a, z / a) : P(); }
  P normal(P p) const { return cross(p).unit(); }
  P rotate(ld angle, P axis) const {
    ld s = sinl(angle), c = cosl(angle);
    P u = axis.unit();
    return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
  }
};
