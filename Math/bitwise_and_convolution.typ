#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Bitwise AND Convolution

$c[k] = sum_(i and j = k) a[i] * b[j]$ を計算する。

$|a| = |b| = 2^N$ である必要がある。

Tips: Bitwise OR Convolutionを用いて計算することも可能。

#sourcecode(```cpp
reverse(all(a)); reverse(all(b));
c = or_conv(a, b);
reverse(all(c));
```)

#sourcefile(read("../Math/bitwise_and_convolution.cpp"), lang: "cpp")
