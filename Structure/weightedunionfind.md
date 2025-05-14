# ✅重み付きUnionFind

## なにこれ
WeightedUnionFind は、頂点の連結状態と重みを管理するつよそうなデータ構造。

## 使い方
### 宣言
```
WeightedUnionFind wuf(N);
```

### 連結
```
wuf.merge(a, b, w);
```

(bの重み) - (aの重み) = w になります
### 連結判定
```
wuf.connected(u, v);
```
連結していたら true が返ってきます


### 重みの差
```
wuf.diff(a, b)
```

(bの重み) - (aの重み)を返します

### グループの要素数
```
wuf.size(i)
```
## 実装
[weightedunionfind.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Structure/weightedunionfind.cpp)
```cpp
template <class Type = ll>
struct WeightedUnionFind {
  WeightedUnionFind() = default;
  explicit WeightedUnionFind(size_t n)
      : m_parentsOrSize(n, -1), m_diffWeights(n) {}
  int find(int i) {
    if (m_parentsOrSize[i] < 0)
      return i;
    const int root = find(m_parentsOrSize[i]);
    m_diffWeights[i] += m_diffWeights[m_parentsOrSize[i]];
    return (m_parentsOrSize[i] = root);
  }
  void merge(int a, int b, Type w) {
    w += weight(a);
    w -= weight(b);
    a = find(a);
    b = find(b);
    if (a != b) {
      if (-m_parentsOrSize[a] < -m_parentsOrSize[b]) {
        swap(a, b);
        w = -w;
      }
      m_parentsOrSize[a] += m_parentsOrSize[b];
      m_parentsOrSize[b] = a;
      m_diffWeights[b] = w;
    }
  }
  Type diff(int a, int b) {
    return (weight(b) - weight(a));
  }
  bool connected(int a, int b) {
    return (find(a) == find(b));
  }
  int size(int i) {
    return -m_parentsOrSize[find(i)];
  }
  vector<int> m_parentsOrSize;
  vector<Type> m_diffWeights;
  Type weight(int i) {
    find(i);
    return m_diffWeights[i];
  }
};
```

## Verify
[AOJ_DSL_1_B](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B)
```cpp
void solve() {
  ll N, Q; cin >> N >> Q;
  WeightedUnionFind wuf(N);
  while (Q--) {
    ll t; cin >> t;
    if (t == 0) {
      ll x, y, z; cin >> x >> y >> z;
      wuf.merge(x, y, z);
    }
    else {
      ll x, y; cin >> x >> y;
      if (!wuf.connected(x, y)) {
        cout << '?' << endl;
      }
      else cout << wuf.diff(x, y) << endl;
    }
  }
}
```
