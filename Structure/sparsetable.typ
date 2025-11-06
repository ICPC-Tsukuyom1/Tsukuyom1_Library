#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Sparse Table

static な配列に対し, 以下の条件を満たす演算を行う区間クエリを, 前計算 $O(N log N)$, クエリ処理 $O(1)$ で解く.

- 結合律 : $(A bullet B) bullet C = A bullet (B bullet C)$
- 冪等性 : $A bullet A = A$

利用時は以下のように `T`, `op` を定義する.

#sourcecode(```cpp
#define T int
#define op(a, b) min(a, b)
```)

#sourcefile(read("../Structure/SparseTable.cpp"), lang: "cpp")
