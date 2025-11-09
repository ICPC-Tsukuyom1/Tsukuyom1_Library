#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 黄金分割探索

区間 `[l, r]` 内の単峰関数 `f` を評価し、最小値付近の点を返す。三分探索より定数倍が小さい。
離散的な関数に関しては、隣接する二項の大小関係による二分探索を行えば良い。

#sourcefile(read("golden_section_search.cpp"), lang: "cpp")
