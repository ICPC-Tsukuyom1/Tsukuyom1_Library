#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bitwise XOR Convolution

$c[k] = sum_(i xor j = k) a[i] * b[j]$ を計算する。

$|a| = |b| = 2^N$ である必要がある。

#sourcefile(read("../Math/bitwise_xor_convolution.cpp"), lang: "cpp")
