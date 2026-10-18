//@aoj GRL_5_A

#include "../../../template.cpp"

#include "../../../Graph/tree-diameter.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  TreeDiameter dia(n);
  rep(i, n - 1) {
    ll a, b, w;
    cin >> a >> b >> w;
    dia.add_edge(a, b, w);
  }
  cout << dia.diameter() << '\n';
}
