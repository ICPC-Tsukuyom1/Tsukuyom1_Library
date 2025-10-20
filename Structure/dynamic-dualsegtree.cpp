struct DynamicDualSeg;
// 必ず vec でなく deque で
deque<DynamicDualSeg> alloc;

struct DynamicDualSeg {
  DynamicDualSeg *lc = 0, *rc = 0;
  ll l, r;
  F v = id;
  F m = id;

  DynamicDualSeg(ll L, ll R) : l(L), r(R) {}
  DynamicDualSeg(ll n) : DynamicDualSeg(0, n) {}

  void _() {
    if (!lc) {
      ll mid = (l + r) / 2;
      alloc.emplace_back(l, mid); lc = &alloc.back();
      alloc.emplace_back(mid, r); rc = &alloc.back();
    }
    lc->effect(l, r, m), rc->effect(l, r, m), m = id;
  }

  // 区間への作用 O(log N)
  void effect(ll L, ll R, F f) {
    if (R <= l || r <= L) return;
    if (L <= l && r <= R) {
      m = merge(m, f);
      v = merge(v, f);
    } else {
      _(), lc->effect(L, R, f), rc->effect(L, R, f);
    }
  }

  // 点取得 O(log N)
  F get(ll i) {
    if (i < l || r <= i) return id;
    if (i <= l && r <= i+1) return v;
    _();
    F lv = lc->get(i), rv = rc->get(i);
    return merge(lv, rv);
  }
};