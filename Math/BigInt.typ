#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== BigInt
符号付き多倍長整数。文字列変換・mul・divは省略OK。(divはmulに依存します)

#sourcefile(read("BigInt.cpp"), lang: "cpp")
