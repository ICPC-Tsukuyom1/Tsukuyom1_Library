struct Point {
    typedef Point P;
    typedef const P& R;
    ld x, y, z;
    explicit Point(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
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
    double phi() const { return atan2(y, x); }
    double theta() const { return atan2(sqrtl(x * x + y * y), z); }
    P unit() const { return *this/abs(); }
    P normal(P p) const { return cross(p).unit(); }
    P rotate(ld angle, P axis) const {
        double s = sinl(angle), c = cosl(angle); P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this)*c - cross(u) * s;
    }
};