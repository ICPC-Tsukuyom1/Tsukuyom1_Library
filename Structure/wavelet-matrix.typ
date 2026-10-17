#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Wavelet Matrix

静的配列を管理する. `wm(l, r)` で `[l, r)` のビューを取得し, それに対して操作を行う.

- `WaveletMatrix(a)`: 構築. $O(N log N)$
- `wm.access(i)`: 元の配列の `a[i]`. $O(log N)$
- `s.size()`: 区間内の要素数.
- `s.kth_smallest(k)`: 0-indexedで `k` 番目の値. $O(log N)$
- `s.count(x)`: `x` の個数. $O(log N)$
- `s.range_freq(upper)`: `upper` 未満の値の個数. $O(log N)$
- `s.range_freq(lower, upper)`: `[lower, upper)` の値の個数。
- `s.max_lt(upper)`: `max {x | x < upper}`. $O(log N)$
- `s.min_ge(lower)`: `min {x | lower <= x}`. $O(log N)$

#sourcefile(read("../Structure/wavelet-matrix.cpp"), lang: "cpp")
