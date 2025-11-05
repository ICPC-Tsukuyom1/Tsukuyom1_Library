struct UFRollback {
  vl e;
  vec<pll> st;
  UFRollback(ll n) : e(n, -1) {}
  ll root(ll x) { return e[x] < 0 ? x : root(e[x]); }
  ll time() { return sz(st); }
  void rollback(ll t) {
    for (ll i = time(); i-- > t;) e[st[i].first] = st[i].second;
    st.resize(t);
  }
  bool unite(ll a, ll b) {
    a = root(a), b = root(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.emplace_back(a, e[a]);
    st.emplace_back(b, e[b]);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
  ll size(ll x) { return -e[root(x)]; }
};