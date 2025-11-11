template<class T=ll>
struct kDTree {
  using I = vec<tuple<ll, ll, T>>::iterator;
  kDTree *l = nullptr, *r = nullptr;
  ll xmin = 2e18, xmax = -2e18, ymin = 2e18, ymax = -2e18;
  ll idx = -1;
  function<T(T, T)> op;
  T e;
  T sum = e;
  kDTree(I begin, I end, auto&& op, T e, bool divx = true) : op(op), e(e) {
    for (auto p = begin; p != end; p++) {
      auto [x, y, w] = *p;
      chmin(xmin, x);
      chmax(xmax, x);
      chmin(ymin, y);
      chmax(ymax, y);
      sum = op(sum, w);
    }
    ll size = end - begin;
    if (size == 1) idx = get<2>(*begin);
    if (size <= 1) return;
    auto cen = begin + size / 2;
    // 円foreachクエリを実装する場合は以下の2行のコメントをトグルすると高速になる
    // if (xmax - xmin > ymax - ymin) {
    if (divx) {
      nth_element(begin, cen, end, [](auto& a, auto& b) { return get<0>(a) < get<0>(b); });
    } else {
      nth_element(begin, cen, end, [](auto& a, auto& b) { return get<1>(a) < get<1>(b); });
    }
    l = new kDTree(begin, cen, op, e, !divx);
    r = new kDTree(cen, end, op, e, !divx);
  }
  // optional
  T prod(ll x1, ll x2, ll y1, ll y2) const {
    if (x2 <= xmin || xmax < x1 || y2 <= ymin || ymax < y1) return 0;
    if (x1 <= xmin && xmax < x2 && y1 <= ymin && ymax < y2) return sum;
    return op(l->prod(x1, x2, y1, y2), r->prod(x1, x2, y1, y2));
  }
  // optional
  void foreach(ll x, ll y, ll R, auto&& f) const {
    auto inside = [](ll dx, ll dy, ll R) {
      return __int128(dx) * dx + __int128(dy) * dy <= __int128(R) * R;
    };
    if (!inside(clamp(x, xmin, xmax) - x, clamp(y, ymin, ymax) - y, R)) return;
    if (idx != -1) {
      f(idx);
      return;
    }
    l->get(x, y, R, f);
    r->get(x, y, R, f);
  }
};