struct SegTree {
  int n = 1;
  vec<T> v;

  // 構築 O(N log N)
  SegTree(int N) {
    while (n < N) n *= 2;
    v.assign(n * 2, e);
  }

  // 一点更新 O(log N)
  // i : [0, n)
  void update(int i, T a) {
    i += n;
    v[i] = a;
    while (i > 1) {
      i /= 2;
      v[i] = op(v[i * 2], v[i * 2 + 1]);
    }
  }

  // 区間総積取得 O(log N)
  // l : [0, n), r : [1, n], l < r
  T query(int l, int r, int x = 1, int lx = 0, int rx = -1) {
    if (rx < 0) rx = n;
    if (rx <= l || r <= lx) return e;
    if (l <= lx && rx <= r) return v[x];
    int m = (lx + rx) / 2;
    T lv = query(l, r, x * 2, lx, m), rv = query(l, r, x * 2 + 1, m, rx);
    return op(lv, rv);
  }

  int max_right(auto f) {
    if (!f(e)) return 0;
    if (f(v[1])) return n;
    T s = e;
    int i = 1;
    while (i < n) {
      int l = i << 1;
      T t = op(s, v[l]);
      if (f(t)) s = t, i = l + 1;
      else i = l;
    }
    return i - n;
  }
};