#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== BFS(幅優先探索)

*なにこれ*

BFS

計算量は $O(V + E)$ だと思います

*必要なライブラリ*

- Graph

*使い方*

#sourcecode(```cpp
bfs(G, s, dist);
```)

G : グラフ

s : 始点

dist : 始点からの距離を格納する配列

返り値：なし　dist が編集される

#sourcefile(read("../Graph/bfs.cpp"), lang: "cpp")