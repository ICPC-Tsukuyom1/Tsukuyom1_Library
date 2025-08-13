# ✅SCC (強連結成分分解)

## なにこれ
強連結成分分解を行う。$O(V + E)$

## 必要なライブラリ
[Graph](https://oxojo.github.io/Oxojo-Library/Graph/Graph)

## 使い方

Verify も参考にしてください。

### 宣言
```
SCC scc(G);
```
G : Graph

### SCC 構築
```
scc.build(G);
```
G : Graph

**G に SCC が構築されるので、ここに元のグラフは代入しない。**

## 実装
```cpp
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
```

## Verify
[AOJ_GRL_3_C](https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C)
```cpp
void solve() {
	ll V, E; cin >> V >> E;
	Graph G(V);
	rep(i, E) {
		ll s, t; cin >> s >> t;
		G.add(s, t, 1, 1);
	}
	SCC scc(G);
	Graph T;
	scc.build(T);
	ll Q; cin >> Q;
	while (Q--) {
		ll x, y; cin >> x >> y;
		cout << (scc[x] == scc[y]) << endl;
	}
}
```
