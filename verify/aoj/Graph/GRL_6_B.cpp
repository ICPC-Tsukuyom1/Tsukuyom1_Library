//@aoj GRL_6_B

#include "../../../template.cpp"
#include "../../../Graph/mincostflow.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll V, E, F;
  cin >> V >> E >> F;
  MinCostFlow mcf(V);
  rep(i, E) {
    ll u, v, c, d;
    cin >> u >> v >> c >> d;
    mcf.add_edge(u, v, c, d);
  }
  auto [flow, cost] = mcf.maxflow(0, V - 1, F);
  if (flow < F)
    cout << -1 << '\n';
  else
    cout << cost << '\n';
}
