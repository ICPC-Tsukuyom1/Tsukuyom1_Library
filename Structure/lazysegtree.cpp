struct LazySeg {
  int n = 1;
  vec<T> v;
  vec<F> m;

  LazySeg(int N) {
    while (n < N) n *= 2;
    v.assign(n * 2, e);
    m.assign(n * 2, id);
  }

  void _(int x, int len) {
    if (m[x] != id) {
      v[x] = apply(m[x], v[x], len);
      if (x < n) {
        m[x * 2] = merge(m[x * 2], m[x]);
        m[x * 2 + 1] = merge(m[x * 2 + 1], m[x]);
      }
      m[x] = id;
    }
  }

  // 区間への作用 O(log N)
  void effect(ll L, ll R, F f, int x = 1, int lx = 0, int rx = -1) {
    if (rx < 0) rx = n;
    _(x, rx - lx);
    if (R <= lx || rx <= L) return;
    if (L <= lx && rx <= R) {
      m[x] = f;
      _(x, rx - lx);
    } else {
      int mid = (lx + rx) / 2;
      effect(L, R, f, x * 2, lx, mid);
      effect(L, R, f, x * 2 + 1, mid, rx);
      v[x] = op(v[x * 2], v[x * 2 + 1]);
    }
  }

  // 区間総積取得 O(log N)
  T query(int L, int R, int x = 1, int lx = 0, int rx = -1) {
    if (rx < 0) rx = n;
    if (R <= lx || rx <= L) return e;
    _(x, rx - lx);
    if (L <= lx && rx <= R) return v[x];
    int mid = (lx + rx) / 2;
    T lv = query(L, R, x * 2, lx, mid);
    T rv = query(L, R, x * 2 + 1, mid, rx);
    return op(lv, rv);
  }
};