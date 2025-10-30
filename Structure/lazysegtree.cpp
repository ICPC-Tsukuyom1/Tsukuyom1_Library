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

  int max_right(auto f) {
    if (!f(e)) return 0;
    if (f(v[1])) return n;
    T s = e;
    int i = 1, len = n;
    while (i < n) {
      _(i, len);
      int l = i << 1;
      _(l, len >> 1);
      T t = op(s, v[l]);
      if (f(t)) s = t, i = l + 1;
      else i = l;
      len >>= 1;
    }
    return i - n;
  }
};