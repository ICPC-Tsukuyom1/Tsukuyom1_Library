struct SparseTable {
  vv<T> st;
  vl lookup;

  SparseTable(const vec<T> &v) {
    ll siz = bit_width((unsigned)sz(v));
    st.assign(siz, vec<T>(sz(v)));
    st[0] = v;
    reps(i, 1, siz) {
      rep(j, sz(v) + 1 - (1 << i)) {
        st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(sz(v) + 1);
    reps(i, 2, sz(lookup)) { lookup[i] = lookup[i >> 1] + 1; }
  }

  T fold(ll l, ll r) {
    ll b = lookup[r - l];
    return op(st[b][l], st[b][r - (1 << b)]);
  }
};
