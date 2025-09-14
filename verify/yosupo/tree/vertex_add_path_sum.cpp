//@yosupo vertex_add_path_sum

// TODO: HLDはもっとまともな問題でVerifyする (Vertex Set Path Composite など?)

#include "../../../template.cpp"

#include "../../../Structure/hld.cpp"

#include "../../../Structure/BIT.cpp"

using Graph = vv<pair<ll, ll>>;

int main() {
  ll n, q;
  cin >> n >> q;
  vl a(n);
  rep(i, n) cin >> a[i];
  Graph g(n);
  rep(i, n - 1) {
    ll u, v;
    cin >> u >> v;
    g[u].emplace_back(1, v);
    g[v].emplace_back(1, u);
  }

  HLD hld(g);

  BIT bit(n);

  rep(i, n) {
    hld.add(i, i, [&](int l, int r) { bit.apply(l, a[i]); });
  }

  rep(i, q) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll p, x;
      cin >> p >> x;
      hld.add(p, p, [&](int l, int r) { bit.apply(l, x); });
    } else {
      ll u, v;
      cin >> u >> v;
      cout << hld.query(
                  u, v, 0LL, [&](ll l, ll r) { return bit.prod(l, r); },
                  [](ll a, ll b) { return a + b; })
           << endl;
    }
  }
}