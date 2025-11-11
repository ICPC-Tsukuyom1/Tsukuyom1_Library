#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Skew Heap

ヒープ同士のマージ、全要素への加算を処理可能な優先度付き (最小) キュー。

全要素加算が必要ない場合、 `lazy`, `_()`, `apply()` を省略出来ます。

#sourcefile(read("../Structure/skew-heap.cpp"), lang: "cpp")
