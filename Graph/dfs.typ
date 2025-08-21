#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 深さ優先探索

*なにこれ*

dfs です　計算量は $O(V + E)$ だった記憶があります

*必要なライブラリ*

- Graph

*つかいかた*

#sourcecode(```cpp
dfs(G, dist, v);
```)

dist に始点からの最短距離が格納される

#sourcefile(read("../Graph/dfs.cpp"), lang: "cpp")