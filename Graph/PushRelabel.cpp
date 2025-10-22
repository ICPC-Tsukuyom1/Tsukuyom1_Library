struct PushRelabel {
    struct Edge {
        ll dest, back;
        ll f, c;
    };
    vv<Edge> g;
    vl ec;
    vec<Edge*> cur;
    vv<ll> hs; vl H;
    PushRelabel(ll n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    void add_edge(ll s, ll t, ll cap, ll rcap = 0) {
        if (s == t) return;
        g[s].emplace_back(t, sz(g[t]), 0, cap);
        g[t].emplace_back(s, sz(g[s]) - 1, 0, rcap);
    }
    void add_flow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f;
        ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(ll s, ll t) {
        ll v = sz(g); H[s] = v; ec[t] = 1;
        vl co(2*v); co[0] = v - 1;
        rep(i, v) cur[i] = g[i].data();
        for (Edge& e : g[s]) add_flow(e, e.c);

        for (ll hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) {
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1) {
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    }
                    if (++co[H[u]], !--co[hi] && hi < v) {
                        rep(i, v) if (hi < H[i] && H[i] < v) {
                            --co[H[i]], H[i] = v + 1;
                        }
                    }
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1) add_flow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            }
        }
    }
    bool leftofMinCut(ll a) { return H[a] >= sz(g); }
};