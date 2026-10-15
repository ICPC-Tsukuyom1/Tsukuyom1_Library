//@yosupo persistent_unionfind

#include "../../../template.cpp"
#include "../../../Structure/UnionFind-rollback.cpp"

struct Query {
  ll u, v, idx;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, q;
  cin >> n >> q;

  vv<ll> child(q + 1);
  vec<Query> queries;
  queries.reserve(q);
  vv<Query> queriesAt(q + 1);
  vl u(q, -1), v(q, -1), t(q, -1), k(q, -2);

  ll out_cnt = 0;
  rep(i, q) {
    ll T, K, U, V;
    cin >> T >> K >> U >> V;
    t[i] = T;
    k[i] = K;
    u[i] = U;
    v[i] = V;
    ll par = (K == -1 ? q : K);
    if (T == 0) {
      child[par].push_back(i);
    } else {
      queriesAt[par].push_back({U, V, out_cnt++});
    }
  }

  vl ans(out_cnt);
  UFRollback uf(n);

  auto dfs = [&](auto&& dfs, ll cur) -> void {
    for (auto& q : queriesAt[cur]) {
      ans[q.idx] = (uf.root(q.u) == uf.root(q.v));
    }
    for (ll nxt : child[cur]) {
      ll tcur = uf.time();
      uf.unite(u[nxt], v[nxt]);
      dfs(dfs, nxt);
      uf.rollback(tcur);
    }
  };

  dfs(dfs, q);

  rep(i, out_cnt) cout << ans[i] << '\n';
  return 0;
}
