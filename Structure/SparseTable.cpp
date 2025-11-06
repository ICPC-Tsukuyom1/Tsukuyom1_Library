struct SparseTable {
  vv<T> st;

  SparseTable(vec<T>& v) : st{v} {
    ll n = sz(v);
    for (ll len = 2; len <= n; len *= 2) {
      st.emplace_back(n - len + 1);
      auto& pre = st[sz(st) - 2];
      auto& cur = st.back();
      rep(i, sz(cur)) cur[i] = op(pre[i], pre[i + len]);
    }
  }

  T fold(ll l, ll r) {
    ll b = __lg(r - l);
    return op(st[b][l], st[b][r - (1 << b)]);
  }
};
