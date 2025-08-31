struct DualSeg {
  int n = 1;
  vec<F> m;

  DualSeg(int N) {
    while (n < N) n *= 2;
    m.assign(n * 2, id);
  }

  void _(int x) {
    if (x < n) {
      m[x * 2] = merge(m[x * 2], m[x]);
      m[x * 2 + 1] = merge(m[x * 2 + 1], m[x]);
      m[x] = id;
    }
  }

  // 区間への作用 O(log N)
  void effect(ll L, ll R, F f, int x = 1, int lx = 0, int rx = -1) {
    if (rx < 0) rx = n;
    _(x);
    if (R <= lx || rx <= L) return;
    if (L <= lx && rx <= R) {
      m[x] = merge(m[x], f);
      _(x);
    } else {
      int mid = (lx + rx) / 2;
      effect(L, R, f, x * 2, lx, mid);
      effect(L, R, f, x * 2 + 1, mid, rx);
    }
  }

  // 点取得 O(log N)
  F get(int i) {
    i += n;
    rrep(j, 0, bit_width((unsigned)i)) { _(i >> j); }
    return m[i];
  }
};