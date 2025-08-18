#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== SegTree

セグメント木。演算および型、単位元はdefineを書き換えてください。
0-indexed, [l, r)の半開区間で使えるようになっています。

*使い方*

- `void update(int i, T a)` : i番目(0-indexed) の値を書き換え $O(log N)$
- `T query(int l, int r)` : 半開区間[l, r)の区間全体への演算結果を得る $O(log N)$

*実装*

#sourcefile(read("../Structure/segtree.cpp"), lang: "cpp")

