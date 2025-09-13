struct Dinic {
	const ll INF = 1e18;

	struct edge {
		ll to, cap, rev, isrev, idx;
	};

	vv<edge> graph;
	vl min_cost, iter;

	explicit Dinic(int V) : graph(V) {}

	void add(ll from, ll to, ll cap, ll idx = -1) {
		graph[from].emplace_back(
			(edge){to, cap, sz(graph[to]), false, idx});
		graph[to].emplace_back(
			(edge){from, 0, sz(graph[from]) - 1, true, idx});
	}

	bool build(int s, int t) {
		min_cost.assign(sz(graph), -1);
		queue<int> que;
		min_cost[s] = 0;
		que.push(s);
		while (!que.empty() && min_cost[t] == -1) {
			int p = que.front(); que.pop();
			for (auto &e : graph[p]) {
				if (e.cap > 0 && min_cost[e.to] == -1) {
					min_cost[e.to] = min_cost[p] + 1;
					que.push(e.to);
				}
			}
		}
		return min_cost[t] != -1;
	}
	ll find(ll idx, const ll t, ll flow) {
		if (idx == t) return flow;
		for (ll &i = iter[idx]; i < sz(graph[idx]); i++) {
			edge &e = graph[idx][i];
			if (e.cap > 0 && min_cost[idx] < min_cost[e.to]) {
				ll d = find(e.to, t, min(flow, e.cap));
				if (d > 0) {
					e.cap -= d;
					graph[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		ll flow = 0;
		while (build(s, t)) {
			iter.assign(sz(graph), 0);
			ll f;
			while ((f = find(s, t, INF)) > 0) flow += f;
		}
		return flow;
	}
	vector<bool> min_cut(int s) {
		vec<bool> used(sz(graph));
		queue<ll> que;
		que.emplace(s);
		used[s] = true;
		while (!que.empty()) {
			ll p = que.front(); que.pop();
			for (auto &e : graph[p]) {
				if (e.cap > 0 && !used[e.to]) {
					used[e.to] = true;
					que.emplace(e.to);
				}
			}
		}
		return used;
	}
};