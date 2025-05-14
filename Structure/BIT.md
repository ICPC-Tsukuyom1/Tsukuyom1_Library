# ✅BIT (Binary Indexed Tree)

2024/06/18 更新しました

## なにこれ
BIT です<br>
一点更新・区間和クエリを処理できます

## 使い方
### 宣言
```
BIT bit(N);
```
N : 要素数
配列を引数にしてもよいです

### 更新
```
bit.apply(i, x);
```
i : 更新する場所（0-indexed）<br>
x : 更新に使う値 ($a_i := a_i + x$ と更新します)

### クエリ
```
s = bit.prod(i);
```
0-indexed の position $i$ に対し、 $\displaystyle \sum_{k=1}^{i-1} a_k$ を返します <br>
区間 [l, r) を引数にすることで、その範囲の sum を得ることができます

### 二分探索
```
ll l = bit.lower_bound(x);
```
lower_bound, upper_bound が使えます

## 実装
[BIT.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Structure/BIT.cpp)
```cpp
template <typename T = ll>
struct BIT {
	ll N;
	vector<T>data;

	BIT() = default;
	explicit BIT(ll N_) : N(N_ + 1), data(N + 1, T()) {}
	explicit BIT(vector<T> &v) : BIT((ll)v.size()) { build(v); }
    
	void build(vector<T> &v) {
		rep(i, N) data[i + 1] = v[i];
		reps(i, 1, N + 1) {
			ll j = i + (i & -i);
			if (j <= N) data[j] += data[i];
		}
	}
		
	void apply(ll k, T &x) {
		for (++k; k <= N; k += k & -k) data[k] += x;
	}

	T prod(ll r) const {
		T ret = T();
		for (; r > 0; r -= r & -r) ret += data[r];
		return ret;
	}

	T prod(ll l, ll r) const { return prod(r) - prod(l); }

	ll lower_bound(T x) const {
		ll i = 0;
		for (ll k = 1 << (__lg(N) + 1); k > 0; k >>= 1) {
			if (i + k <= N && data[i + k] < x) {
				x -= data[i + k];
				i += k;
			}
		}
		return i;
	}

	ll upper_bound(T x) const {
		ll i = 0;
		for (ll k = 1 << (__lg(N) + 1); k > 0; k >>= 1) {
			if (i + k <= N && data[i + k] <= x) {
				x -= data[i + k];
				i += k;
			}
		}
		return i;
	}
};
```

## Verify
[AOJ_DSL_2_B](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B)
```cpp
void solve() {
	ll N, Q; cin >> N >> Q;
	BIT bit(N);
	while (Q--) {
		ll t, x, y; cin >> t >> x >> y;
		if (t == 0) bit.add(x, y);
		else cout << bit.prod(x, y) << endl;
	}
}
```
