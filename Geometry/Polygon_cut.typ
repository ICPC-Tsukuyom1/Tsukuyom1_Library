#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Polygon Cut
凸多角形を直線で切断した片方の多角形を求める。
直線 s -> e の向きで切断したときに、その向きで見て右側にある多角形を返します。
#sourcefile(read("../Geometry/Polygon_cut.cpp"), lang: "cpp")