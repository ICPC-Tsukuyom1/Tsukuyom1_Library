struct MST {
    ll cost;
    Edges edges;
};
MST Kruskal(Edges &edges, ll V) {
    sort(edges.begin(),edges.end(), [](Edge &a, Edge &b) {
        return a.cost < b.cost;
    });
    UnionFind uf(V);
    ll total = 0ll;
    Edges es;
    for (auto e : edges) {
        if (!uf.same(e.from, e.to)) {
            es.emplace_back(e);
            total += e.cost;
            uf.unite(e.from, e.to);
        }
    }
    return {total, es};
}
