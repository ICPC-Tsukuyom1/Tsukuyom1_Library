#Lazy Segment Tree

## なにこれ

## 使い方
### 宣言
## 実装
```cpp
long long bit_width(long long x) {
  if (x == 0) {
    return 0;
  }
  return 64 - __builtin_clzll(x);
}

long long bit_ceil(long long x) {
  return 1LL << bit_width(x - 1);
}

template <typename T, typename F>
class LazySegmentTree {
  size_t n;
  size_t height;
  function<T(T, T)> _op;
  function<F(F, F)> _merge;
  function<T(F, T, size_t)> _apply;
  T e;
  F id;
  vector<T> data;
  vector<F> lazy;

  T eval(size_t i) {
    if (lazy[i] == id) return data[i];
    data[i] = _apply(lazy[i], data[i], 1<<(height - bit_width(i)));
    if (i < n) {
      lazy[2 * i] = _merge(lazy[2 * i], lazy[i]);
      lazy[2 * i + 1] = _merge(lazy[2 * i + 1], lazy[i]);
    }
    lazy[i] = id;
    return data[i];
  }

public:
  LazySegmentTree(size_t n, const function<T(T,T)> &op, const function<F(F,F)> &merge, const function<T(F,T,size_t)> &apply, const T &e, const F &id)
    : n(bit_ceil(n)), height(bit_width(this->n)),
    _op(op), _merge(merge), _apply(apply),
    e(e), id(id)
  {
    data.assign(2 * this->n, e);
    lazy.assign(2 * this->n, id);
  }

  LazySegmentTree(const vector<T> &v, const function<T(T,T)> &op, const function<F(F,F)> &merge, const function<T(F,T,size_t)> &apply, const T &e, const F &id)
  : LazySegmentTree(v.size(), op, merge, apply, e, id)
  {
    memcpy(&data[n], v.data(), v.size() * sizeof(T));
    for (int i = n - 1; i > 0; --i)
      data[i] = op(data[2 * i], data[2 * i + 1]);
  }

  void apply(size_t l, size_t r, F f) {
    if(l == r) return;
    l += n;
    r += n;
    size_t l0 = l, r0 = r;
    for(size_t i=height; i>0; --i) {
      eval(l >> i);
      eval((r-1) >> i);
    }
    for (; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        lazy[l] = _merge(lazy[l], f);
        ++l;
      }
      if (r % 2 == 1) {
        --r;
        lazy[r] = _merge(lazy[r], f);
      }
    }
    l = l0;
    r = r0 - 1;
    while(l > 1) {
      l /= 2;
      r /= 2;
      data[l] = _op(eval(2 * l), eval(2 * l + 1));
      data[r] = _op(eval(2 * r), eval(2 * r + 1));
    }
  }

  T prod(size_t l, size_t r) {
    l += n;
    r += n;
    for(size_t i=height; i>0; --i) {
      eval(l >> i);
      eval((r-1) >> i);
    }
    T res_l = e, res_r = e;
    for (; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        res_l = _op(res_l, eval(l++));
      }
      if (r % 2 == 1) {
        res_r = _op(eval(--r), res_r);
      }
    }
    return _op(res_l, res_r);
  }

  T get(size_t i) {
    return prod(i, i + 1);
  }

  T operator[](size_t i) {
    return get(i);
  }

};
```

## Verify
[AOJ_DSL_2_E](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_E)
```cpp
int main() {
  int n, q;
  cin >> n >> q;
  LazySegmentTree<int, int> seg(n, [](int a, int b) { return a + b; }, [](int a, int b) { return a + b; }, [](int f, int g, size_t len) { return f + g; }, 0, 0);
  for(int i=0; i<q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      s--;
      t--;
      seg.apply(s, t + 1, x);
    } else {
      int i;
      cin >> i;
      i--;
      cout << seg.get(i) << endl;
    }
  }
}
```
