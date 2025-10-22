struct DynamicSeg {
  DynamicSeg *lc = 0, *rc = 0;
  ll l, r;
  T v;

  DynamicSeg(ll L, ll R) : l(L), r(R), v(e) {}

  // 構築 O(1)
  DynamicSeg(ll n) : DynamicSeg(0, n) {}

  void _() {
    if (!lc) {
      ll m = (l + r) / 2;
      lc = new DynamicSeg(l, m);
      rc = new DynamicSeg(m, r);
    }
  }

  // 一点更新 O(log N)
  // i : [0, n)
  void update(ll i, T a) {
    if (l == i && r == i + 1) v = a;
    else if (l <= i && i < r) {
      _();
      lc->update(i, a);
      rc->update(i, a);
      auto lv = lc->v, rv = rc->v;
      v = op(lv, rv);
    }
  }

  T query(ll L, ll R) {
    if (R <= l || r <= L) return e;
    if (L <= l && r <= R) return v;
    _();
    auto lv = lc->query(L, R), rv = rc->query(L, R);
    return op(lv, rv);
  }
};