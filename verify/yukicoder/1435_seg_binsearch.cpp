//@yukicoder 1435

#include "../../template.cpp"

const ll INF = 4e18;

struct Node {
  ll mn1, mn2, mx;
};

#define T Node
#define e \
  Node { INF, INF, -INF }

ll second_min(Node a, Node b) {
  vl x = {a.mn1, a.mn2, b.mn1, b.mn2};
  sort(all(x));
  return x[1];
}

#define op(a, b) \
  Node { min(a.mn1, b.mn1), second_min(a, (b)), max(a.mx, b.mx) }

#include "../../Structure/segtree.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;
  vl a(n);
  rep(i, n) cin >> a[i];

  SegTree seg(n);
  rep(i, n) { seg.update(i, Node{a[i], INF, a[i]}); }

  ll ans = 0;
  rep(l, n) {
    int r = seg.max_right([](Node x) -> bool {
      if (x.mn2 >= INF / 2) return true;
      return x.mx <= x.mn1 + x.mn2;
    });
    chmin(r, n);
    ans += max(0, r - l - 1);
    seg.update(l, e);
  }

  cout << ans << '\n';
  return 0;
}
