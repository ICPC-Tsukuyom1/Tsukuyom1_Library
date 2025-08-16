# convolution mod998244353

## なにこれ
与えられた数列 $a, b$ に対して、畳み込みを行なった数列を生成する
具体的には、 $c_k = \sum_{k=i+J} a_i b_j mod 998244353$
となるような数列 $c$ を生成する

## 必要なライブラリ
[power](https://github.com/Oxojo/Tsukuyom1_Library/blob/main/Math/power.cpp)

## つかいかた
```
vl c = conv9(a, b);
```
畳み込みされた数列が返ってくる

## verify
[yosupo_ConvMod](https://judge.yosupo.jp/submission/307921)

## 実装
void solve(){
    ll N, M; cin >> N >> M;
    vl a(N), b(M);
    rep(i, N) cin >> a[i];
    rep(i, M) cin >> b[i];
    vl c = conv9(a, b);
    rep(i, N+M-1) cout << c[i] << " \n"[i == N+M-2];
    return;
}
```