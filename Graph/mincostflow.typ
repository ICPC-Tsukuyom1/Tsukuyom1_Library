#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== MinCostFlow

最小費用流。 `slope` 、 `maxflow` は流量を $F$ として $O(F E log V)$ 、 `setpi` は $O(V E)$

負サイクルを持つグラフには利用できない。

`slope()` は `{流量, min cost}` の列を返す。 `maxflow()` はその末尾の要素。それぞれ第三引数は流量の上限。

最小費用が負になる場合は先に `setpi(始点)` を実行する。 (利用しない場合実装を省略して良い)

#sourcefile(read("../Graph/mincostflow.cpp"), lang: "cpp")