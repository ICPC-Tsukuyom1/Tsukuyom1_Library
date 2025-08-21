#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== convolution mod998244353

*なにこれ*

与えられた数列 $a, b$ に対して、畳み込みを行なった数列を生成する
具体的には、 $c_k = sum_(k=i+J) a_i b_j "mod" 998244353$
となるような数列 $c$ を生成する

*必要なライブラリ*

- power

*つかいかた*

#sourcecode(```cpp
vl c = conv9(a, b);
```)

畳み込みされた数列が返ってくる

#sourcefile(read("../Math/convolution_mod.cpp"), lang: "cpp")
