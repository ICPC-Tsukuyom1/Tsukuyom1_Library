#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== isinPolygon
点が多角形の内部に含まれていれば $2$, 辺上にあれば $1$, 外部にあれば $0$ を返す。
#sourcefile(read("../Geometry/isinpolygon.cpp"), lang: "cpp")