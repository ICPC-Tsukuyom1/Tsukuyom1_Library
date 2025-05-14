# ✅UnionFind

## なにこれ
UnionFind は、頂点の連結状態を管理するつよそうなデータ構造。

## 使い方
### 宣言
```
UnionFind uf(N);
```

### 連結
```
uf.unite(u, v);
```

### 連結判定
```
uf.same(u, v);
```
連結していたら true が返ってきます

### 連結成分の個数
```
uf.count()
```

## 実装
[unionfind.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Structure/unionfind.cpp)
```cpp
struct UnionFind {
    ll cnt;
    vector<ll> par, siz;
    UnionFind(ll N) : par(N, -1LL), siz(N, 1LL) {cnt = N;}

    ll root(ll v) {
        if (par[v] == -1) return v;
        return par[v] = root(par[v]);
    }
    
    bool same(ll u, ll v) {
        return root(u) == root(v);
    }

    bool unite(ll u, ll v) {
        u = root(u); v = root(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) swap(u, v);
        par[v] = u;
        siz[u] += siz[v];
        cnt--;
        return true;
    }

    ll count() {
        return cnt;
    }
};
```

## Verify
[AOJ_DSL_1_A](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_A)
```cpp
void solve() {
	ll n, q; cin >> n >> q;
	UnionFind uf(n);
	while (q--) {
		ll t, x, y; cin >> t >> x >> y;
		if (t == 0) uf.unite(x, y);
		else cout << uf.same(x, y) << endl;
	}
}
```
