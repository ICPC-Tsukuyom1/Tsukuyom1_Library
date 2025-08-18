const ll INF = 4e18;

#define T ll
#define e INF
#define op(a, b) min(a, b)

struct SegTree {
  int n = 1;
  vector<T> v;
  SegTree(int N) {
    while(n < N) n *= 2;
    v.assign(n * 2, e);
  }
  void update(int i, T a) {
    i += n;
    v[i] = a;
    while(i > 1) {
      i /= 2;
      v[i] = op(v[i * 2], v[i * 2 + 1]);
    }
  }
  T _query(int l, int r, int x, int lx, int rx) {
    if(rx <= l || r <= lx) return e;
    if(lx >= l && rx <= r) return v[x];
    int m = (lx + rx) / 2;
    return op(
      _query(l, r, x * 2, lx, m),
      _query(l, r, x * 2 + 1, m, rx)
    );
  }
  T query(int l, int r) {
    return _query(l, r, 1, 0, n);
  }
};

#undef T
#undef e
#undef op