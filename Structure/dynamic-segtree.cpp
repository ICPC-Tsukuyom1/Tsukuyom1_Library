struct DynamicSeg;
// 必ず vec でなく deque で
deque<DynamicSeg> alloc;

struct DynamicSeg {
  DynamicSeg *lc = 0, *rc = 0;
  ll l, r;
  T v;

  DynamicSeg(ll L, ll R) : l(L), r(R), v(e) {}
  DynamicSeg(ll n) : DynamicSeg(0, n) {}

  void _() {
    if (!lc) {
      ll m = (l + r) / 2;
      alloc.emplace_back(l, m);
      lc = &alloc.back();
      alloc.emplace_back(m, r);
      rc = &alloc.back();
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

  ll max_right(ll L, auto f) {
    T s = e;
    auto dfs = [&](auto&& self, DynamicSeg* n) -> ll {
      if (n->r <= L) return L;
      if (L <= n->l) {
        T t = op(s, n->v);
        if (f(t)) {
          s = t;
          return n->r;
        }
        if (n->l + 1 == n->r) return n->l;
      }
      n->_();
      ll res = self(self, n->lc);
      return (res < n->lc->r) ? res : self(self, n->rc);
    };
    return dfs(dfs, this);
  }
};
