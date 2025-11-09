#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 2次元 BIT

2 次元の BIT 。矩形和・点加算クエリを $O(log H log W)$ で処理可能。
初期化 $O(H W)$ 。

それぞれのインターフェースは0-indexed、 $[x_1, x_2), [y_1, y_2)$ のような半開区間として扱われる。

#sourcefile(read("../Structure/BIT2d.cpp"), lang: "cpp")
