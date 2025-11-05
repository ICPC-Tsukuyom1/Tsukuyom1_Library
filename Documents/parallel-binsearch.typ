#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 並列二分探索

`bool` を返す関数列 $f_k (x)$ が $x$ に対して単調である ($x <= x_k$ で `true` 、$x > x_k$ で `false` となる) とき、この境界 $x_0, x_1, ..., x_n$ を高速に求めることができる。
また、 $f_k (x)$ はランダムアクセス可能でなくても、イテレーション可能であればよい。( $f_k (x)$ の導出に $f_k (x-1)$ が必要でもよい)

各クエリに対し、そのLとRを記録しておく。ここから、関数列を順に舐めながらL, Rを更新する。合計の計算量は $O(N log N log Q)$ となる。 ( $N$ は探索範囲の大きさ、$Q$はクエリの数)

以下、疑似コード。

#sourcecode(```cpp
vl l(q, 0), r(q, n);
rep(_, 30) {
  vvl checks(n);
  rep(i, q) if (l[i] + 1 < r[i]) {
    checks[(l[i] + r[i]) / 2].pb(i);
  }
  rep(i, n) {
    for(auto idx: checks[i]) {
      if (f_idx(i)) l[idx] = i;
      else r[idx] = i;
    }
  }
}
```)
