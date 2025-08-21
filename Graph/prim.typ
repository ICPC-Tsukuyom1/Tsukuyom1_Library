#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== プリム法

*なにこれ*

最小全域木を構築する。たぶん計算量は $O(E + V log V)$ かも

*必要なライブラリ*

- Graph

*つかいかた*

#sourcecode(```cpp
MST T = Prim(G)
```)

合計コストと、最小全域木をなす辺集合が返ってくる

#sourcefile(read("../Graph/Prim.cpp"), lang: "cpp")