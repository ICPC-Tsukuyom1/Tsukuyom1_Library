#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== エラトステネスの篩

*なにこれ*

$N$ 以下の素数の個数を、前処理 $O(N log log N)$ 各クエリ $O(1)$ で行います。

*つかいかた*

*宣言*

#sourcecode(```cpp
Eratosthenes E(N);
```)

宣言と同時に前処理が行われます。

*クエリ*

#sourcecode(```cpp
c = E.count(n);
```)

n 以下の素数の個数が返ってきます。

#sourcefile(read("../Math/Eratosthenes.cpp"), lang: "cpp")
