//@aoj GRL_2_A

#include "../../../template.cpp"
#include "../../../Graph/Kruskal.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll V, E;
  cin >> V >> E;
  vec<Edge> edges(E);
  rep(i, E) cin >> edges[i].from >> edges[i].to >> edges[i].cost;
  cout << Kruskal(edges, V).cost << '\n';
}
