struct UnionFind {
    ll cnt;
    vector<ll> par, siz;
    UnionFind(ll N) : par(N, -1LL), siz(N, 1LL) {cnt = N;}

    ll root(ll v) {
        if (par[v] == -1) return v;
        return par[v] = root(par[v]);
    }
    
    bool same(ll u, ll v) {
        return root(u) == root(v);
    }

    bool unite(ll u, ll v) {
        u = root(u); v = root(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) swap(u, v);
        par[v] = u;
        siz[u] += siz[v];
        cnt--;
        return true;
    }

	ll size(ll v) {
		v = root(v);
		return siz[v];
	}

    ll count() {
        return cnt;
    }
};