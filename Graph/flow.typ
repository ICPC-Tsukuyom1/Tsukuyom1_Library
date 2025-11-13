#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Dinic

$n$ 頂点 $m$ 辺のグラフにおける最大フローを求める。 計算量は、一般に $Omicron(n^2 m)$\
各頂点を通れるフロー量の平均値が $k$ 以下ならば、計算量は $Omicron(k sqrt(n) m)$\
具体例としては、二部マッチング問題が、$O(sqrt(n) m)$である。

#sourcefile(read("../Graph/flow.cpp"), lang: "cpp")