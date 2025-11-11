template <class T>
struct SkewHeap {
  using H = SkewHeap<T>;
  using P = H*;
  T val, laz;
  H *l, *r;
  SkewHeap(T& v) : val(v), laz(0), l(0), r(0) {}
  void _() {
    if (!laz) return;
    if (l) l->laz += laz;
    if (r) r->laz += laz;
    val += laz;
    laz = 0;
  }
  T top() { return _(), val; }
  static P merge(P x, P y) {
    if (!x || !y) return x ?: y;
    x->_();
    if (x->top() > y->top()) swap(x, y);
    swap(x->l, x->r = merge(x->r, y));
    return x;
  }
  static P pop(P x) { return x->_(), merge(x->l, x->r); }
  static P push(P x, T& val) { return merge(x, new H(val)); }
  static void apply(P x, T& laz) {
    x->laz += laz;
    x->_();
  }
};