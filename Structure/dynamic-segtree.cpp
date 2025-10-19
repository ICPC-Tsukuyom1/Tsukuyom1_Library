struct DynamicSeg {
  static deque<DynamicSeg> alloc;
  // DynamicSeg *lc = 0, *rc = 0;
  int lc = -1, rc = -1;
  ll l, r;
  T v;

  DynamicSeg(ll L, ll R) : l(L), r(R), v(e) {}

  // 構築 O(1)
  DynamicSeg(ll n) : DynamicSeg(0, n) {}

  void _() {
    if (lc < 0) {
      ll m = (l + r) / 2;
      lc = alloc.size(), alloc.emplace_back(l, m);
      rc = alloc.size(), alloc.emplace_back(m, r);
    }
  }

  // 一点更新 O(log N)
  // i : [0, n)
  void update(ll i, T a) {
    if (l == i && r == i + 1)
      v = a;
    else if (l <= i && i < r) {
      _();
      alloc[lc].update(i, a);
      alloc[rc].update(i, a);
      auto lv = alloc[lc].v, rv = alloc[rc].v;
      v = op(lv, rv);
    }
  }

  T query(ll L, ll R) {
    if (R <= l || r <= L)
      return e;
    if (L <= l && r <= R)
      return v;
    _();
    auto lv = alloc[lc].query(L, R), rv = alloc[rc].query(L, R);
    return op(lv, rv);
  }
};

deque<DynamicSeg> DynamicSeg::alloc = {};