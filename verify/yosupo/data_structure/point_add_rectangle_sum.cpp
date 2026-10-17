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

  map<ll, int> ix, iy;
  rep(i, n) { ix[pts[i][0]]; iy[pts[i][1]]; }
  rep(i, q) {
    if (ops[i][0] == 0) { ix[ops[i][1]]; iy[ops[i][2]]; }
    else { ix[ops[i][1]]; ix[ops[i][3]]; iy[ops[i][2]]; iy[ops[i][4]]; }
  }
  int nx = 0, ny = 0;
  for (auto &[k, v] : ix) v = nx++;
  for (auto &[k, v] : iy) v = ny++;

  BIT2dSparse<ll> b(nx);

  // 事前登録: 点更新の座標と、矩形和に使う prefix 境界
  rep(i, n) b.request(ix[pts[i][0]], iy[pts[i][1]]);
  rep(i, q) {
    if (ops[i][0] == 0) b.request(ix[ops[i][1]], iy[ops[i][2]]);
    else {
      b.request_prefix(ix[ops[i][3]], iy[ops[i][4]]);
      b.request_prefix(ix[ops[i][3]], iy[ops[i][2]]);
      b.request_prefix(ix[ops[i][1]], iy[ops[i][4]]);
      b.request_prefix(ix[ops[i][1]], iy[ops[i][2]]);
    }
  }
  b.build();

  rep(i, n) b.add(ix[pts[i][0]], iy[pts[i][1]], pts[i][2]);
  rep(i, q) {
    if (ops[i][0] == 0) b.add(ix[ops[i][1]], iy[ops[i][2]], ops[i][3]);
    else out << b.sum(ix[ops[i][1]], ix[ops[i][3]], iy[ops[i][2]], iy[ops[i][4]]) << '\n';
  }
}
