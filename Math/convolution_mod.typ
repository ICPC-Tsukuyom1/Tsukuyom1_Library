#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== convolution

与えられた数列 $a, b$ に対して、$c_k = sum_(k=i+j) a_i b_j "mod" p$ となる数列 $c$ を生成する。

#sourcefile(read("../Math/convolution_mod.cpp"), lang: "cpp")
