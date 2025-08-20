#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bitwise OR Convolution

$c[k] = sum_(i or j = k) a[i] * b[j]$ を計算する。

$|a| = |b| = 2^N$ である必要がある。

#sourcefile(read("../Math/bitwise_convolution.cpp"), lang: "cpp")

== Bitwise AND Convolution

Bitwise OR Convolutionを用いて計算可能。 (TODO)

#sourcecode(```cpp
reverse(all(a)); reverse(all(b));
c = or_conv(a, b);
reverse(all(c));
```)

== Bitwise XOR Convolution

TODO