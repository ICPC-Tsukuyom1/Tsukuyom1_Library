template <class Type = ll>
struct WeightedUnionFind {
  WeightedUnionFind() = default;
  explicit WeightedUnionFind(size_t n)
      : m_parentsOrSize(n, -1), m_diffWeights(n) {}
  int find(int i) {
    if (m_parentsOrSize[i] < 0)
      return i;
    const int root = find(m_parentsOrSize[i]);
    m_diffWeights[i] += m_diffWeights[m_parentsOrSize[i]];
    return (m_parentsOrSize[i] = root);
  }
  void merge(int a, int b, Type w) {
    w += weight(a);
    w -= weight(b);
    a = find(a);
    b = find(b);
    if (a != b) {
      if (-m_parentsOrSize[a] < -m_parentsOrSize[b]) {
        swap(a, b);
        w = -w;
      }
      m_parentsOrSize[a] += m_parentsOrSize[b];
      m_parentsOrSize[b] = a;
      m_diffWeights[b] = w;
    }
  }
  Type diff(int a, int b) {
    return (weight(b) - weight(a));
  }
  bool connected(int a, int b) {
    return (find(a) == find(b));
  }
  int size(int i) {
    return -m_parentsOrSize[find(i)];
  }
  vector<int> m_parentsOrSize;
  vector<Type> m_diffWeights;
  Type weight(int i) {
    find(i);
    return m_diffWeights[i];
  }
};
