#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== lineInter
直線同士の交点を求める。交わっていれば `{true, Intersection}`、平行または同一直線で交点が一意に定まらなければ `{false, (0, 0)}` を返す。
#sourcefile(read("../Geometry/lineInter.cpp"), lang: "cpp")
