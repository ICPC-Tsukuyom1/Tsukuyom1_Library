#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== lineInter
直線同士の交点を求める。返り値は交わっていなければ `{0, {0, 0}}` 、交わっていれば `{1, Intersection}`。
#sourcefile(read("../Geometry/lineInter.cpp"), lang: "cpp")