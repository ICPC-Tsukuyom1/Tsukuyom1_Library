#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Undo可能UnionFind

巻き戻しが可能な UnionFind 。
現在時刻を `time()` で取得でき、`rollback(t)` で時刻 `t` に巻き戻せる。
`unite()`, `root()` は $O(log N)$ 、`size()`, `time()` は $O(1)$ 、`rollback()` は巻き戻す回数を $k$ として $O(k)$ で動作する。

#sourcefile(read("../Structure/UnionFind-rollback.cpp"), lang: "cpp")
