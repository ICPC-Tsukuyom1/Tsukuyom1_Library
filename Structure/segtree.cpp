template<class T>
struct SegTree {
  using F = function<T(T, T)>;

  int n = 1;
  vector<T> v;
  F op;
  T e;

  // 構築 O(N log N)
  SegTree(int N, F op, T e): op(op), e(e) {
    while(n < N) n *= 2;
    v.assign(n * 2, e);
  }

  // 一点更新 O(log N)
  // i : [0, n)
  void update(int i, T a) {
    i += n;
    v[i] = a;
    while(i > 1) {
      i /= 2;
      v[i] = op(v[i * 2], v[i * 2 + 1]);
    }
  }

  T _(int l, int r, int x, int lx, int rx) {
    if(rx <= l || r <= lx) return e;
    if(l <= lx && rx <= r) return v[x];
    int m = (lx + rx) / 2;
    return op(
      _(l, r, x * 2, lx, m),
      _(l, r, x * 2 + 1, m, rx)
    );
  }
  
  // 区間総積取得 O(log N)
  // l : [0, n), r : [1, n], l < r
  T query(int l, int r) {
    return _(l, r, 1, 0, n);
  }
};