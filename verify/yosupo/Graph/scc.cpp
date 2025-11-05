//@yosupo scc
#include "../../../template.cpp"
#include "../../../Graph/SCC.cpp"
void solve() {
    ll n, m; cin >> n >> m;
    vv<ll> g(n);
    rep(i, m) {
        ll u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
    }
    SCC scc(g);
    cout << sz(scc.dag) << endl;
    rep(i, sz(scc.dag)) {
        cout << sz(scc.belong(i));
        for (auto &e : scc.belong(i)) {
            cout << ' ' << e;
        }
        cout << endl;
    }
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}