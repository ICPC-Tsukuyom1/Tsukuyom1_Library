#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== NTT / convolution

modint を係数とする畳み込みを数論変換 (NTT) で計算する。法 $m$ は原始根 $g$ をもつ素数で、
$m - 1$ が $2$ の冪で割り切れること。$g$ は省略時 $3$ (998244353 などはこれでよい)。
片方が小さいとき (60 項以下) は naive $O(n m)$ で計算する。

#sourcefile(read("ntt.cpp"), lang: "cpp")
