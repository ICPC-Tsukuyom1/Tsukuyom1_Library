//@yosupo line_add_get_min
#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/LiChaoTree.cpp"
struct query {
  ll t;
  ll a, b;
};
void solve() {
  ll N, Q;
  in >> N >> Q;
  vl x;
  vec<query> q;
  rep(i, N) {
    ll a, b;
    in >> a >> b;
    q.emplace_back(0, a, b);
  }
  while (Q--) {
    ll t;
    in >> t;
    if (t == 0) {
      ll a, b;
      in >> a >> b;
      q.emplace_back(t, a, b);
    } else {
      ll p;
      in >> p;
      q.emplace_back(t, p, 0);
      x.emplace_back(p);
    }
  }
  if (x.empty()) { return; }
  LCTree lct(x);
  rep(i, sz(q)) {
    if (q[i].t == 0) {
      lct.update(q[i].a, q[i].b);
    } else {
      ll ans = lct.query(q[i].a);
      out << ans << '\n';
    }
  }
}
int main() {
  ll T = 1;
  // in >> T;
  while (T--) { solve(); }
}