#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== solveLinear
連立一次方程式 $bold(A x) = bold(b)$ を解く。
解が存在しなければ空の二次元配列を返す。
解が存在する場合、1 行目に特殊解、2 行目以降に解空間の基底ベクトルを格納した二次元配列を返す。

#sourcefile(read("solveLinear.cpp"), lang: "cpp")