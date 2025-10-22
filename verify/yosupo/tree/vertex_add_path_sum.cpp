//@yosupo vertex_add_path_sum

// TODO: HLDはもっとまともな問題でVerifyする (Vertex Set Path Composite など?)

#include "../../../Structure/BIT.cpp"
#include "../../../Structure/hld.cpp"
#include "../../../template.cpp"

using Graph = vv<ll>;

int main() {
  ll n, q;
  cin >> n >> q;
  vl a(n);
  rep(i, n) cin >> a[i];
  Graph g(n);
  rep(i, n - 1) {
    ll u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  HLD<ll> hld(g);

  BIT bit(n);

  rep(i, n) {
    hld.process(i, i, [&](int l, int r) { bit.apply(l, a[i]); });
  }

  rep(i, q) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll p, x;
      cin >> p >> x;
      hld.process(p, p, [&](int l, int r) { bit.apply(l, x); });
    } else {
      ll u, v;
      cin >> u >> v;
      cout << hld.queryPath(
                  u, v, 0LL, [&](ll l, ll r) { return bit.prod(l, r); },
                  [](ll a, ll b) { return a + b; })
           << endl;
    }
  }
}