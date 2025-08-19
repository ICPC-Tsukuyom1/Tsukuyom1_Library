#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== Convex Hull
凸包を求める。`strict` が `true` なら辺上の点を含めず、`false` なら含める。
#sourcefile(read("../Geometry/convex_hull.cpp"), lang: "cpp")