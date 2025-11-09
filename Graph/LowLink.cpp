template <typename G>
struct LowLink {
    ll n;
    const G g;
    vl ord, low, arti;
    vec<pll> bridge;

    LowLink(G g) : n(sz(g)), g(g), ord(sz(g), -1), low(sz(g), -1) {
        ll k = 0;
        rep(i, n) {
            if (ord[i] == -1) k = dfs(i, k, -1);
        }
    }

    ll dfs(ll x, ll k, ll p) {
        low[x] = (ord[x] = k++);
        ll cnt = 0;
        bool is_arti = false, second = false;
        for (auto &e : g[x]) {
            if (ord[e] == -1) {
                cnt++;
                k = dfs(e, k, x);
                chmin(low[x], low[e]);
                is_arti |= (p != -1) && (low[e] >= ord[x]);
                if (ord[x] < low[e]) bridge.emplace_back(min(x, e), max(x, e));
            } else if (e != p || second) {
                chmin(low[x], ord[e]);
            } else {
                second = true;
            }
        }
        is_arti |= p == -1 && cnt > 1;
        if (is_arti) arti.emplace_back(x);
        return k;
    }
};