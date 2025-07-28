# Rolling Hash

## なにこれ
Rolling Hash は、文字列一致判定を高速に行うアルゴリズムである。
## 使い方
### 宣言
```
RollingHash rh(s);
```
文字列 s を渡すことで、各iに対して [0, i) のHash関数の結果を構築する。

### get
```
rh.get(l, r)
```
[l, r)区間の文字列のハッシュ値を取得する。

## 実装
[RollingHash.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Structure/RollingHash.cpp)
```cpp
struct RollingHash{
    ll base = 150, Hash = (1LL<<61) - 1;
    string S;
    vector<ll> hashed, power;
    ll mul(ll a, ll b){
        return __int128_t(a) * b % Hash;
    };
    RollingHash(const string &S){
        ll N = S.size();
        hashed.assign(N+1, 0);
        power.assign(N+1, 0);
        power[0] = 1;
        rep(i, N){
            power[i+1] = mul(power[i], base);
            hashed[i+1] = mul(hashed[i], base) + S[i];
            if(hashed[i+1] >= Hash) hashed[i+1] -= Hash;
        }
    }
    ll get(ll l, ll r){
        ll ret = hashed[r] + Hash - mul(hashed[l], power[r-l]);
        if(ret >= Hash) ret -= Hash;
        return ret;
    }
};
```

## Verify
[AOJ_ALDS1_14_B String Search](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja)
```cpp
void solve() {
  string T, P; cin >> T >> P;
  RollingHash rh(T), rp(P);
  ll N = T.size(), M = P.size();
  ll p = rp.get(0, M);
  rep(i, N-M+1){
    if(rh.get(i, i+M) == p){
      cout << i << endl;
    }
  }
}
```
