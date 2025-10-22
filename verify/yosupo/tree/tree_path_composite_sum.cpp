//@yosupo tree_path_composite_sum

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

// "../../../Graph/Graph.cpp" を、ll以外の重みを許容するように改変

template <class T = ll>
struct Edge {
  ll from, to;
  T cost;

  Edge(ll from, ll to, T cost = 1ll) : from(from), to(to), cost(cost) {}
};

template <class T = ll>
struct Graph {
  vector<vector<Edge<T>>> G;
  Graph() = default;

  explicit Graph(ll N) : G(N) {}

  size_t size() const { return G.size(); }

  void add(ll from, ll to, T cost = 1ll, bool direct = 0) {
    G[from].emplace_back(from, to, cost);
    if (!direct) G[to].emplace_back(to, from, cost);
  }

  vector<Edge<T>>& operator[](const int& k) { return G[k]; }
};

vec<mint> a;

#define V pair<mint, ll>
#define E pair<mint, ll>
#define put_edge(v, edge) \
  E { v.first *edge.cost.first + edge.cost.second *v.second, v.second }
#define put_vert(e, i) \
  V { e.first + a[i], e.second + 1 }
#define op(a, b) \
  E { a.first + b.first, a.second + b.second }
#define ee \
  E { 0, 0 }

#include "../../../Graph/rerooting.cpp"

int main() {
  ll n;
  cin >> n;
  a.resize(n);
  rep(i, n) cin >> a[i];
  Graph<pair<mint, mint>> g(n);
  rep(i, n - 1) {
    ll u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    g.add(u, v, {b, c});
  }
  auto res = rerooting(g);
  rep(i, n) { cout << res[i].first << endl; }
}
