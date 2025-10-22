struct DynamicLazySeg;
// 必ず vec でなく deque で
deque<DynamicLazySeg> alloc;

struct DynamicLazySeg {
  DynamicLazySeg *lc = 0, *rc = 0;
  ll l, r;
  T v = e;
  F m = id;

  DynamicLazySeg(ll L, ll R) : l(L), r(R) {}

  // 要素数から構築 O(1)
  DynamicLazySeg(ll n) : DynamicLazySeg(0, n) {}

  void _() {
    if (!lc) {
      ll m = l + (r - l) / 2;
      alloc.emplace_back(l, m); lc = &alloc.back();
      alloc.emplace_back(m, r); rc = &alloc.back();
    }
    if (m != id) lc->effect(l, r, m), rc->effect(l, r, m), m = id;
  }

  // 区間への作用 O(log N)
  void effect(ll L, ll R, F f) {
    if (R <= l || r <= L) return;
    if (L <= l && r <= R) {
      m = merge(m, f);
      auto len = r - l;
      v = apply(f, v, len);
    } else {
      _(), lc->effect(L, R, f), rc->effect(L, R, f);
      v = op(lc->v, rc->v);
    }
  }

  // 区間総積取得 O(log N)
  T query(ll L, ll R) {
    if (R <= l || r <= L) return e;
    if (L <= l && r <= R) return v;
    _();
    auto lv = lc->query(L, R), rv = rc->query(L, R);
    return op(lv, rv);
  }
};