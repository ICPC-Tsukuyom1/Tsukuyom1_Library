//@yosupo staticrmq

#include "../../template.cpp"

const ll INF = 4e18;

#include "../../Structure/segtree.cpp"

int main()
{
  int n, q;
  cin >> n >> q;
  SegTree<ll> st(
    n,
    [](ll a, ll b) { return min(a, b); },
    INF
  );
  rep(i, n)
  {
    int x;
    cin >> x;
    st.update(i, x);
  }
  rep(i, q)
  {
    int l, r;
    cin >> l >> r;
    cout << st.query(l, r) << endl;
  }
  return 0;
}
