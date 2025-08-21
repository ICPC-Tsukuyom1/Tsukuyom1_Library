#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== Projection
`reflect` が `true` なら点から直線へ下した垂線の足、`false` なら直線に関して対称な点を返す。
#sourcefile(read("../Geometry/projection.cpp"), lang: "cpp")