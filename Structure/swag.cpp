struct SWAG {
  #define get(v) (sz(v) ? v.back().second : (e))
  using vp = vec<pair<T, T>>;
  vp f, b;
  SWAG() {}
  void _() {
    ll n = sz(f) + sz(b), s = n / 2 + (sz(f) ? 0 : n & 1);
    vp v = f;
    reverse(all(v));
    copy(all(b), back_inserter(v));
    f.clear(), b.clear();
    rrep(i, 0, s) push_front(v[i].first);
    reps(i, s, n) push_back(v[i].first);
  }
  T front() { return (sz(f) ? f.back() : b.front()).first; }
  T back() { return (sz(b) ? b.back() : f.front()).first; }
  void push_front(T x) { f.emplace_back(x, op(x, get(f))); }
  void push_back(T x) { b.emplace_back(x, op(get(b), x)); }
  void pop_front() {
    if (empty(f)) _();
    f.pop_back();
  }
  void pop_back() {
    if (empty(b)) _();
    b.pop_back();
  }
  T query() { return op(get(f), get(b)); }
};