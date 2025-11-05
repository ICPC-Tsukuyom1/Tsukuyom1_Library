#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Manacher

`p[0][i]` : `i - 1` 文字目と `i` 文字目の間を中心とした最長回文部分列の半径、
`p[1][i]` : `i` 文字目を中心とした最長回文部分列の半径。
最長回文部分列の長さは `p[0][i] * 2` または `p[1][i] * 2 + 1`

#sourcefile(read("../Strings/Manacher.cpp"), lang: "cpp")
