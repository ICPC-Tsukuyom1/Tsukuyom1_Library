template <typename T = ll, typename F = ll>
struct SegTree {
  ll N, siz;
  vector<T> seg;

  const F f;
  const T ti;

  SegTree() = default;

  explicit SegTree(ll n, const F f, const T &Ti) : N(n), f(f), ti(Ti) {
    siz = 1;
    while (siz < N) siz <<= 1;
    seg.assign(2 * siz, ti);
  }

  explicit SegTree(const vector<T> &v, const F f, const T &ti) : SegTree((ll)v.size(), f, ti) {
    build(v);
  }

  void build(const vector<T> &v) {
    if (N != v.size()) return;
    rep(i, N) seg[i + siz] = v[i];
    for (ll i = siz - 1; i > 0; i--) {
      seg[i] = f(seg[2 * i], seg[2 * i + 1]);
    }
  }

  void update(ll k, const T &x) {
    k += siz;
    seg[k] = x;
    while (k >>= 1) {
      seg[k] = f(seg[2 * k], seg[2 * k + 1]);
    }
  }

  T get(ll k) const {
    return seg[k + siz];
  }

  T operator[](const ll &k) const {return get(k);}

  void apply(ll k, const T &x) {
    k += siz;
    seg[k] = f(seg[k], x);
    while (k >>= 1) {
      seg[k] = f(seg[2 * k], seg[2 * k + 1]);
    }
  }

  T prod(ll l, ll r) const {
    T L = ti, R = ti;
    for (l += siz, r += siz; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = f(L, seg[l++]);
      if (r & 1) R = f(seg[--r], R);
    }
    return f(L, R);
  }

  T all_prod() const { return seg[1]; }
};

template <typename T, typename F>
SegTree<T, F> get_segtree(ll N, const F &f, const T &ti) {
  return SegTree{N, f, ti};
}

template <typename T, typename F>
SegTree<T, F> get_segtree(const vector<T> &N, const F &f, const T &ti) {
  return SegTree{N, f, ti};
}
