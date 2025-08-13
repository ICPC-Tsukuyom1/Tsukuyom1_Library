struct SCC {
	Graph &g;
	Graph gg, rg;
	vector<ll> cmp, ord, use;

	SCC(Graph &g): g(g), gg(g.size()), rg(g.size()), cmp(g.size(), -1), use(g.size()) {
		rep(i, g.size()) {
			for (auto e : g[i]) {
				gg.add(i, e.to, 1, 1);
				rg.add(e.to, i, 1, 1);
			}
		}
	}

	ll operator[](ll k) { return cmp[k]; }

	void dfs(ll p) {
		if (use[p]) return;
		use[p] = 1;
		for (auto e : gg[p]) dfs(e.to);
		ord.push_back(p);
	}

	void rdfs(ll p, ll cnt) {
		if (cmp[p] != -1) return;
		cmp[p] = cnt;
		for (auto e : rg[p]) rdfs(e.to, cnt);
	}

	void build(Graph &t) {
		rep(i, gg.size()) {
			dfs(i);
		}
		reverse(all(ord));
		ll ptr = 0;
		for (ll i : ord) {
			if (cmp[i] == -1) rdfs(i, ptr), ptr++;
		}

		t = Graph(ptr);
		rep(i, g.size()) {
			for (auto &e : g[i]) {
				ll x = cmp[i], y = cmp[e.to];
				if (x == y) continue;
				t.add(x, y, 1, 1);
			}
		}
	}
};