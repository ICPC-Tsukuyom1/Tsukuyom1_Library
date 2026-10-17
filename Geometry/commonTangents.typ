#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== commonTangents
2 円の共通接線を求める。各接線の `s` が c1 の接点、`e` が c2 の接点。2 円が接する場合は縮退した接線を接点 1 点（`s == e`）として 1 本だけ返す。同心円など定まらない場合は空。
#sourcefile(read("../Geometry/commonTangents.cpp"), lang: "cpp")
