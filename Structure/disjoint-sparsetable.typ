#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Disjoint Sparse Table

static な配列に対し, 以下の条件を満たす演算を行う区間クエリを, 前計算 $O(N log N)$, クエリ処理 $O(1)$ で解く.

- 結合律 : $(A bullet B) bullet C = A bullet (B bullet C)$

冪等性は不要.

利用時は以下のように `T`, `op` を定義する.

#sourcecode(```cpp
#define T ll
#define op(a, b) a + b
```

#sourcefile(read("../Structure/disjoint-sparsetable.cpp"), lang: "cpp")
