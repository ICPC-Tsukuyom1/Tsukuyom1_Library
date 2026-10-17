#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== isConvex
単純多角形が凸かを判定する。頂点数が 3 未満、または自己交差する多角形は `false` を返す。
#sourcefile(read("../Geometry/isconvex.cpp"), lang: "cpp")
