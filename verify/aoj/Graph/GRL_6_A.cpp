//@aoj GRL_6_A

#include "../../../template.cpp"
#include "../../../Graph/flow.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll V, E;
  cin >> V >> E;
  Dinic dinic(V);
  rep(i, E) {
    ll u, v, c;
    cin >> u >> v >> c;
    if (u == v) continue;
    dinic.add(u, v, c);
  }
  cout << dinic.max_flow(0, V - 1) << '\n';
}
