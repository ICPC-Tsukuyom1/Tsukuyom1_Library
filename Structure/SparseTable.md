# ✅Sparse Table

## なにこれ
static な配列に対し, 以下の条件を満たす演算を行う区間クエリを, 前計算 $O(N \log{N})$, クエリ処理 $O(1)$ で解く.

- 結合律 : $(A \bullet B) \bullet C = A \bullet (B \bullet C)$
- 冪等性 : $A \bullet A = A$

## 使い方

### 宣言
```
SparseTable S(vector<T>v, f);
```
配列 v, 演算 f で初期化する.

### クエリ処理
```
T ans = S.fold(l, r);
```
区間 $[l, r)$ に対する演算結果を返す. 0-indexed.

## 実装
[SparseTable.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Structure/SparseTable.cpp)
```cpp
template <typename T = ll, typename F = ll>
struct SparseTable {
	F f;
	vector<vector<T>> st;
	vector<ll> lookup;

	SparseTable() = default;

	explicit SparseTable(const vector<T> &v, const F &f) : f(f) {
		const ll N = (ll)v.size();
		ll siz = 0;
		ll tmp = N;
		while (tmp != 0) {
			siz++; tmp >>= 1;
		}
		st.assign(siz, vector<T>(N));
		rep(i, v.size()) {
			st[0][i] = v[i];
		}
		reps(i, 1, siz) {
			rep(j, N + 1 - (1 << i)) {
				st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
		lookup.resize(v.size() + 1);
		reps(i, 2, lookup.size()) {
			lookup[i] = lookup[i >> 1] + 1;
		}
	}

	inline T fold(ll l, ll r) const {
		ll b = lookup[r - l];
		return f(st[b][l], st[b][r - (1 << b)]);
	}
};
```

## Verify
[Static RMQ](https://judge.yosupo.jp/problem/staticrmq)
```cpp
void solve() {
	ll N, Q; cin >> N >> Q;
	vector<ll>A(N);
	rep(i, N) cin >> A[i];
	SparseTable S(A, [](ll a, ll b) {return min(a, b);});
	while (Q--) {
		ll l, r; cin >> l >> r;
		cout << S.fold(l, r) << endl;
	}
}
```
