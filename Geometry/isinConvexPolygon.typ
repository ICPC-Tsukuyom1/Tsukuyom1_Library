#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== isinConvexPolygon
反時計回りの凸多角形に対し、点が内部なら `2`, 辺上なら `1`, 外部なら `0` を返す。
頂点 `S[0]` からの扇形を二分探索するので $O(log n)$。
#sourcefile(read("../Geometry/isinConvexPolygon.cpp"), lang: "cpp")
