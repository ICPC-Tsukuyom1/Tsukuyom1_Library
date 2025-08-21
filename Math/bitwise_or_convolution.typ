#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bitwise OR Convolution

$c[k] = sum_(i or j = k) a[i] * b[j]$ を計算する。

$|a| = |b| = 2^N$ である必要がある。

#sourcefile(read("../Math/bitwise_or_convolution.cpp"), lang: "cpp")
