struct DisjointSparseTable {
  vv<T> st;

  DisjointSparseTable(vec<T>& v) : st{v} {
    ll n = sz(v);
    for (ll len = 2; len <= n; len *= 2) {
      auto& row = st.emplace_back(n);
      for (ll i = 0; i < n; i += len * 2) {
        ll mid = min(i + len, n);
        ll r = min(i + len * 2, n);
        row[mid - 1] = v[mid - 1];
        rrep(j, i, mid - 1) row[j] = op(v[j], row[j + 1]);
        if (mid >= n) continue;
        row[mid] = v[mid];
        reps(j, mid + 1, r) row[j] = op(row[j - 1], v[j]);
      }
    }
  }

  T fold(ll l, ll r) {
    --r;
    if (l == r) return st[0][l];
    ll b = __lg(l ^ r);
    return op(st[b][l], st[b][r]);
  }
};
