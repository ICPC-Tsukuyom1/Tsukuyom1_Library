struct maxMatch {
  ll n;
  vv<ll> g;
  vl mt;
  vl ev, gr;
  vec<pll> nx;
  ll st;
  ll group(ll x) {
    if (gr[x] == -1 || ev[gr[x]] != st) return gr[x];
    return gr[x] = group(gr[x]);
  }
  void match(ll p, ll b) {
    ll d = mt[p];
    mt[p] = b;
    if (d == -1 || mt[d] != p) return;
    if (nx[p].second == -1) {
      mt[d] = nx[p].first;
      match(nx[p].first, d);
    } else {
      match(nx[p].first, nx[p].second);
      match(nx[p].second, nx[p].first);
    }
  }
  bool arg() {
    ev[st] = st;
    gr[st] = -1;
    nx[st] = pll(-1, -1);
    queue<ll> q;
    q.push(st);
    while (!q.empty()) {
      ll a = q.front();
      q.pop();
      for (auto b : g[a]) {
        if (b == st) continue;
        if (mt[b] == -1) {
          mt[b] = a;
          match(a, b);
          return 1;
        }
        if (ev[b] == st) {
          ll x = group(a), y = group(b);
          if (x == y) continue;
          ll z = -1;
          while (x != -1 || y != -1) {
            if (y != -1) swap(x, y);
            if (nx[x] == pll(a, b)) {
              z = x;
              break;
            }
            nx[x] = pll(a, b);
            x = group(nx[mt[x]].first);
          }
          for (ll v : {group(a), group(b)}) {
            while (v != z) {
              q.push(v);
              ev[v] = st, gr[v] = z;
              v = group(nx[mt[v]].first);
            }
          }
        } else if (ev[mt[b]] != st) {
          ev[mt[b]] = st;
          nx[b] = pll(-1, -1);
          nx[mt[b]] = pll(a, -1);
          gr[mt[b]] = b;
          q.push(mt[b]);
        }
      }
    }
    return 0;
  }
  maxMatch(vv<ll>& g) : n(sz(g)), g(g), mt(n, -1), ev(n, -1), gr(n), nx(n) {
    for (st = 0; st < n; st++)
      if (mt[st] == -1) arg();
  }
  vec<pll> max_match() {
    vec<pll> res;
    rep(i, n) if (i < mt[i]) res.emplace_back(i, mt[i]);
    return res;
  }
};