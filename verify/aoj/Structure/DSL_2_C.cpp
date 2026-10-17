//@aoj DSL_2_C

#include "../../../template.cpp"
#include "../../../Structure/kd-tree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  if (n == 0) {
    ll q;
    cin >> q;
    rep(i, q) cout << '\n';
    return 0;
  }
  vec<tuple<ll, ll, ll>> src;
  src.reserve(n);
  vl X(n), Y(n);
  rep(i, n) {
    ll x, y;
    cin >> x >> y;
    X[i] = x, Y[i] = y;
    src.emplace_back(x, y, i);
  }
  kDTree<> kd(all(src), [](ll a, ll b) { return min(a, b); }, 0);
  ll q;
  cin >> q;
  ostringstream os;
  while (q--) {
    ll sx, tx, sy, ty;
    cin >> sx >> tx >> sy >> ty;
    // 長方形を囲む円を求め，その円内の点を列挙して長方形でふるい分ける
    ll cx = sx + (tx - sx) / 2, cy = sy + (ty - sy) / 2;
    ll dx = max(cx - sx, tx - cx), dy = max(cy - sy, ty - cy);
    ll r = (ll)ceill(sqrtl((long double)dx * dx + (long double)dy * dy)) + 1;
    vl res;
    kd.foreach(cx, cy, r, [&](ll id) {
      if (sx <= X[id] && X[id] <= tx && sy <= Y[id] && Y[id] <= ty) res.push_back(id);
    });
    sort(all(res));
    for (ll id : res) os << id << '\n';
    os << '\n';
  }
  cout << os.str();
}
