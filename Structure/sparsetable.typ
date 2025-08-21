#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Sparse Table

*なにこれ*

static な配列に対し, 以下の条件を満たす演算を行う区間クエリを, 前計算 $O(N log N)$, クエリ処理 $O(1)$ で解く.

- 結合律 : $(A bullet B) bullet C = A bullet (B bullet C)$
- 冪等性 : $A bullet A = A$

*使い方*

*宣言*

#sourcecode(```cpp
SparseTable S(vector<T>v, f);
```)

配列 v, 演算 f で初期化する.

*クエリ処理*

#sourcecode(```cpp
T ans = S.fold(l, r);
```)

区間 $[l, r)$ に対する演算結果を返す. 0-indexed.

#sourcefile(read("../Structure/SparseTable.cpp"), lang: "cpp")
