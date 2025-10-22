struct Edge {
    ll from, to, cost;
    Edge (ll from, ll to, ll cost = 1ll) : from(from), to(to), cost(cost) {}
};
struct Graph {
    vector<vector<Edge>> G;
    Graph() = default;
    explicit Graph(ll N) : G(N) {}
    size_t size() const {
        return G.size();
    }
    void add(ll from, ll to, ll cost = 1ll, bool direct = 0) {
        G[from].emplace_back(from, to, cost);
        if (!direct) G[to].emplace_back(to, from, cost);
    }
    vector<Edge> &operator[](const int &k) {
        return G[k];
    }
};
using Edges = vector<Edge>;
