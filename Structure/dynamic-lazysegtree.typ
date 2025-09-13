#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Dynamic Lazy Segment Tree

通常の遅延セグメント木の能力に加え、構築が $O(1)$ となっています。 ( $N = 10^18$ でも動作します)

#sourcefile(read("../Structure/dynamic-lazysegtree.cpp"), lang: "cpp")