//@yosupo point_add_rectangle_sum

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;

#include "../../../Structure/BIT2d-sparse.cpp"

int main() {
  ll n, q;
  in >> n >> q;
  vec<array<ll, 3>> pts(n);
  rep(i, n) in >> pts[i][0] >> pts[i][1] >> pts[i][2];
  // 0: "x y w" 点加算 / 1: "l y1 r y2" 矩形和
  vec<array<ll, 5>> ops(q);
  rep(i, q) {
    in >> ops[i][0];
    if (ops[i][0] == 0) in >> ops[i][1] >> ops[i][2] >> ops[i][3];
    else in >> ops[i][1] >> ops[i][2] >> ops[i][3] >> ops[i][4];
  }

  // 加算する点を元の座標値で集めて渡す (座圧は内部で行われる).
  vec<pll> points(n);
  rep(i, n) points[i] = {pts[i][0], pts[i][1]};
  rep(i, q) if (ops[i][0] == 0) points.push_back({ops[i][1], ops[i][2]});

  BIT2dSparse<ll> b(points);

  rep(i, n) b.add(pts[i][0], pts[i][1], pts[i][2]);
  rep(i, q) {
    if (ops[i][0] == 0) b.add(ops[i][1], ops[i][2], ops[i][3]);
    else out << b.sum(ops[i][1], ops[i][3], ops[i][2], ops[i][4]) << '\n';
  }
}
