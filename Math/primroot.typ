#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== 原始根
3 以上の素数 $p$ に関して、ある $1 <= r < p$ が存在して、$r^i != 1 (mod p)$ $(i = 1, ..., p - 2)$ を満たすとき、$r$ を法 $p$ に対する原始根と呼ぶ。

#sourcefile(read("primroot.cpp"), lang: "cpp")