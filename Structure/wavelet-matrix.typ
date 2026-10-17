#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Wavelet Matrix

静的な配列の区間順序統計・頻度クエリ. 座標圧縮を内蔵し, 負数や `long long` の最小値・最大値にも対応する. 更新・区間和は非対応.

C++20 と `template.cpp` が必要. `WaveletMatrix<T>` の既定型は `ll`; `T` は比較可能な値型. 添字・順位・個数は `ll` だが, 内部配列に `int` を使うため $N <= "INT_MAX"$ を前提とする.

`wm(l, r)` は半開区間 `[l, r)` の非所有ビュー `Span` を $O(1)$ で返す. ビューはコピー・再代入でき, クエリで区間は変化しない.

- `WaveletMatrix(a)`: 構築. 元の配列は変更しない.
- `wm.access(i)`: 元の配列の `a[i]`.
- `s.size()`: 区間長.
- `s.kth_smallest(k)`: 小さい方から `k` 番目の値 (0-indexed).
- `s.count(x)`: `x` の個数.
- `s.range_freq(upper)`: `upper` 未満の値の個数.
- `s.range_freq(lower, upper)`: `lower` 以上 `upper` 未満の値の個数. `upper <= lower` なら 0.
- `s.prev_value(upper)`: `upper` 未満の最大値.
- `s.next_value(lower)`: `lower` 以上の最小値.

`prev_value`・`next_value` は対象の値が存在しない場合の動作は未定義 (利用者が保証する): 呼ぶ前に `prev_value` は `s.range_freq(upper) > 0`, `next_value` は `s.range_freq(lower) < s.size()` を確認する. 空配列・空区間も扱えるが, 空区間への `kth_smallest` は不可.

引数の範囲は利用者が保証する (`assert` は置かない): $0 <= l <= r <= N$, `access` は $0 <= i < N$, `kth_smallest` は `0 <= k < s.size()`.
ビューの使用中は元の WM を生存させ, 移動・再代入しないこと. 一時 WM から作ったビューを保存してはならない.

配列に現れる相異なる値の個数 (座標圧縮辞書のサイズ) を $sigma$, $B = ceil(log_2(max(1, sigma)))$ とすると, 構築は通常 $O(N log N)$.
`kth_smallest` と `access` は $O(B)$; 値を受け取る `count`・`range_freq`・`prev_value`・`next_value` は辞書の二分探索を含め $O(log sigma + B)$.
`wm(l, r)` は $O(1)$.
`stable_partition` の補助メモリを確保できない場合, 構築は最悪 $O(N log N + N B log N)$.
各段は 64 bit のビット列とブロック累積和で約 $12 ceil(N/64)$ byte と管理領域を使用し, 圧縮辞書と構築時の $O(N)$ 作業領域が加わる.

#sourcecode(```cpp
vl a = {-3, 7, 7, 2};
WaveletMatrix wm(a);
auto s = wm(0, 4);
auto x = s.kth_smallest(1);         // 2
ll c = s.range_freq(2LL, 8LL);     // 3
ll p = s.prev_value(2LL);          // -3
ll d = wm(1, 3).count(7LL);        // 2
```)

#sourcefile(read("../Structure/wavelet-matrix.cpp"), lang: "cpp")
