#define T ll
#define e 0LL
#define F pair<ll, ll>
#define id pair{1LL, 0LL}
#define op(a, b) (((a)+(b)) % mod)
// (F:before, F:append) -> F:merged
#define merge(a, b) pair{(a).first * (b).first % mod, ((a).second * (b).first + (b).second) % mod};
// (F, T, len) -> T
#define apply(f, x, l) ((f).first * (x) + (f).second * (l)) % mod;

struct LazySeg {
  LazySeg *lc = 0, *rc = 0;
  ll l, r;
  T v=e;
  F m=id;
  LazySeg(ll L, ll R): l(L), r(R) {}

  // 要素数から構築 O(1)
  LazySeg(ll n) : LazySeg(0, n) {}

  void _() {
    if (!lc) {
      ll m = l + (r-l)/2;
      lc = new LazySeg(l, m); rc = new LazySeg(m, r);
    }
    if (m != id)
      lc->effect(l,r,m), rc->effect(l,r,m), m = id;
  }

  // 区間への作用 O(log N)
  void effect(ll L, ll R, F f) {
    if (R <= l || r <= L) return;
    if (L <= l && r <= R) {
      m = merge(m, f);
      v = apply(f, v, r - l);
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
    return op(lc->query(L, R), rc->query(L, R));
  }
};

#undef T
#undef e
#undef F
#undef id
#undef op
#undef merge
#undef apply
