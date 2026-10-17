#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 円と円の交点
存在しない場合は `(-inf, -inf)` を返す（`inf` は `Point.cpp` で定義される真の無限大）。
#sourcefile(read("../Geometry/ccInter.cpp"), lang: "cpp")
