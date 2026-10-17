#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Binary Trie

- `T`, `op(T a, T b) -> T`, `e() -> T` ：可換モノイド
- `B`：使用するビット数 (1〜63)

`size`, `xor_all`, `query_all` は $O(1)$, 他は $O(B)$.

#sourcefile(read("../Structure/binary-trie.cpp"), lang: "cpp")
