/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Graph/flow.cpp */
struct Dinic {
  const ll INF = 1e18;

  struct edge {
    ll to, cap, rev, isrev, idx;
  };

  vv<edge> graph;
  vl min_cost, iter, vs, es;  // vs, es は find() の明示スタック

  Dinic(int V) : graph(V) {}

  void add(ll from, ll to, ll cap, ll idx = -1) {
    graph[from].emplace_back(edge{to, cap, sz(graph[to]), false, idx});
    graph[to].emplace_back(edge{from, 0, sz(graph[from]) - 1, true, idx});
  }

  bool build(int s, int t) {
    min_cost.assign(sz(graph), -1);
    queue<int> que;
    min_cost[s] = 0;
    que.push(s);
    while (!que.empty()) {
      int p = que.front();
      que.pop();
      for (auto &e : graph[p]) {
        if (e.cap > 0 && min_cost[e.to] == -1) {
          min_cost[e.to] = min_cost[p] + 1;
          que.push(e.to);
        }
      }
    }
    return min_cost[t] != -1;
  }
  // 増加パスを 1 本探して流す。再帰せず明示スタックで辿る。
  ll find(ll idx, const ll t, ll flow) {
    vs.assign(1, idx);
    es.clear();
    while (!vs.empty()) {
      ll v = vs.back();
      if (v == t) {
        ll f = flow;
        rep(i, sz(es)) f = min(f, graph[vs[i]][es[i]].cap);
        rep(i, sz(es)) {
          edge &e = graph[vs[i]][es[i]];
          e.cap -= f;
          graph[e.to][e.rev].cap += f;
        }
        return f;
      }
      bool advanced = false;
      for (ll &i = iter[v]; i < sz(graph[v]); i++) {
        edge &e = graph[v][i];
        if (e.cap > 0 && min_cost[v] + 1 == min_cost[e.to]) {
          es.push_back(i);
          vs.push_back(e.to);
          advanced = true;
          break;
        }
      }
      if (!advanced) {
        // 行き止まり。順方向の容量は以後増えないので、この phase では再訪不要
        min_cost[v] = -1;
        vs.pop_back();
        if (!es.empty()) es.pop_back();
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
  vec<bool> min_cut(int s) {
    vec<bool> used(sz(graph));
    queue<ll> que;
    que.emplace(s);
    used[s] = true;
    while (!que.empty()) {
      ll p = que.front();
      que.pop();
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