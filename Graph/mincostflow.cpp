#include <bits/extc++.h>

const ll INF = 1e18;

struct MinCostFlow {
  struct Edge {
    ll from, to, rev, cap, cost, flow;
  };
  ll n;
  vv<Edge> ed;
  vl seen;
  vl dist, pi;
  vec<Edge*> par;

  MinCostFlow(ll n) : n(n), ed(n), seen(n), dist(n), pi(n), par(n) {}

  void add_edge(ll from, ll to, ll cap, ll cost) {
    if (from == to) return;
    ed[from].push_back(Edge{from, to, sz(ed[to]), cap, cost, 0});
    ed[to].push_back(Edge{to, from, sz(ed[from]) - 1, 0, -cost, 0});
  }

  void path(ll s) {
    fill(all(seen), 0);
    fill(all(dist), INF);
    dist[s] = 0;
    ll di;
    using Pq = __gnu_pbds::priority_queue<pll>;
    Pq q;
    vec<Pq::point_iterator> its(n);
    q.push({0, s});
    while (!q.empty()) {
      s = q.top().second;
      q.pop();
      seen[s] = 1;
      di = dist[s] + pi[s];
      for (Edge& e : ed[s])
        if (!seen[e.to]) {
          ll val = di - pi[e.to] + e.cost;
          if (e.cap - e.flow > 0 && val < dist[e.to]) {
            dist[e.to] = val;
            par[e.to] = &e;
            if (its[e.to] == q.end()) its[e.to] = q.push({-dist[e.to], e.to});
            else q.modify(its[e.to], {-dist[e.to], e.to});
          }
        }
    }
    rep(i, n) pi[i] = min(pi[i] + dist[i], INF);
  }

  vec<pll> slope(ll s, ll t, ll f = INF) {
    vec<pll> res;
    ll totflow = 0, totcost = 0;
    res.push_back({0, 0});
    while (totflow < f && (path(s), seen[t])) {
      ll fl = INF;
      for (Edge* x = par[t]; x; x = par[x->from])
        fl = min(fl, x->cap - x->flow);
      fl = min(fl, f - totflow);

      for (Edge* x = par[t]; x; x = par[x->from]) {
        x->flow += fl;
        ed[x->to][x->rev].flow -= fl;
      }
      ll d = pi[t];
      totflow += fl;
      totcost += fl * d;
      res.push_back({totflow, totcost});
    }
    return res;
  }

  // optional
  pll maxflow(ll s, ll t, ll f = INF) { return slope(s, t, f).back(); }

  // read document
  void setpi(ll s) {
    fill(all(pi), INF);
    pi[s] = 0;
    ll it = n, ch = 1;
    ll v;
    while (ch-- && it--) {
      rep(i, n) {
        if (pi[i] != INF) {
          for (Edge& e : ed[i]) {
            if (e.cap && (v = pi[i] + e.cost) < pi[e.to]) pi[e.to] = v, ch = 1;
          }
        }
      }
    }
    assert(it >= 0);
  }
};