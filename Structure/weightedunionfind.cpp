template <class T = ll>
struct WeightedUnionFind {
  vl par;
  vec<T> wd;
  WeightedUnionFind(ll n) : par(n, -1), wd(n) {}
  ll find(int i) {
    if (par[i] < 0) return i;
    ll root = find(par[i]);
    wd[i] += wd[par[i]];
    return par[i] = root;
  }
  void merge(int a, int b, T w) {
    w += weight(a), w -= weight(b);
    a = find(a), b = find(b);
    if (a == b) return;
    if (par[a] > par[b]) swap(a, b), w = -w;
    par[a] += par[b];
    par[b] = a;
    wd[b] = w;
  }
  int size(int i) { return -par[find(i)]; }
  T weight(int i) {
    find(i);
    return wd[i];
  }
};