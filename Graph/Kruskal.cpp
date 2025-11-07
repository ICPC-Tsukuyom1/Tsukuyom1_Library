#include "../Structure/unionfind.cpp"

struct Edge {
  ll from, to, cost;
};
struct MST {
  ll cost;
  vec<Edge> edges;
};
MST Kruskal(vec<Edge> &edges, ll V) {
  sort(edges.begin(), edges.end(),
       [](Edge &a, Edge &b) { return a.cost < b.cost; });
  UnionFind uf(V);
  ll total = 0ll;
  vec<Edge> es;
  for (auto e : edges) {
    if (uf.root(e.from) != uf.root(e.to)) {
      es.emplace_back(e);
      total += e.cost;
      uf.unite(e.from, e.to);
    }
  }
  return {total, es};
}
