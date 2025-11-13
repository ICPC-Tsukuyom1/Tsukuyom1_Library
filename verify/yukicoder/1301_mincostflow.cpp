//@yukicoder 1301

#include "../../template.cpp"
#include "../../Graph/mincostflow.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  MinCostFlow mcf(n);

  rep(i, m) {
    ll u, v, c, d;
    cin >> u >> v >> c >> d;
    u--, v--;
    mcf.add_edge(u, v, 1, c);
    mcf.add_edge(v, u, 1, c);
    mcf.add_edge(u, v, 1, d);
    mcf.add_edge(v, u, 1, d);
  }
  
  cout << mcf.maxflow(0, n-1, 2).second << endl;
}
