# Segment Tree

## なにこれ
Segment Tree は、一点更新・区間二項演算のクエリを処理するデータ構造である。

## 使い方
### 宣言
```
auto seg = get_segtree(N, f, ti);
```
構造体として宣言することもできるが、なぜかこっちの方が確実。<br>
N : 要素数、f : モノイド演算子、ti : 演算の単位元

```
auto seg = get_segtree(v, f, ti);
```
要素数の代わりに配列そのものを渡すことで、最初に配列の各要素を持ったセグ木を構築できる。

### update
```
seg.update(k, x)
```
k 番目（0-indexed）の値を x に変更する。

### get
```
seg.set(k)
```
k 番目（0-indexed）の値を取得する。

### apply
```
seg.apply(k, x)
```
k 番目（0-indexed）の値に、それと x で二項演算を行った結果を代入する。

### prod
```
seg.prod(l, r)
```
区間 [l, r) において、その中の要素すべてに対し順に二項演算を行った結果を取得する。

## 実装
```cpp
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
```

## Verify
[AOJ_DSL_2_A](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A)
```cpp
void solve() {
  ll N, Q; cin >> N >> Q;
  auto seg = get_segtree(N, [](ll a, ll b){return min(a, b);}, (ll)(1ll<<31)-1);
  while (Q--) {
    ll t, x, y;  cin >> t >> x >> y;
    if (t == 0) {
      seg.update(x, y);
    }
    else {
      cout << seg.prod(x, y + 1) << endl;
    }
  }
}
```
