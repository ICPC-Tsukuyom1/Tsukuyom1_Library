template <class Type = ll>
struct WeightedUnionFind {
  vl par;
  vec<Type> wd;
  WeightedUnionFind() = default;
  explicit WeightedUnionFind(size_t n) : par(n, -1), wd(n) {}
  ll find(int i) {
    if (par[i] < 0) return i;
    const ll root = find(par[i]);
    wd[i] += wd[par[i]];
    return (par[i] = root);
  }
  void merge(int a, int b, Type w) {
    w += weight(a), w -= weight(b);
    a = find(a), b = find(b);
    if (a == b) return;
    if (-par[a] < -par[b]) {
      swap(a, b);
      w = -w;
    }
    par[a] += par[b];
    par[b] = a;
    wd[b] = w;
  }
  Type diff(int a, int b) { return (weight(b) - weight(a)); }
  bool same(int a, int b) { return (find(a) == find(b)); }
  int size(int i) { return -par[find(i)]; }
  Type weight(int i) {
    find(i);
    return wd[i];
  }
};