#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== SWAG

`deque` の上位互換。
型 `T` 、二項演算 `op` 、単位元 `e` を与えて利用する。結合法則が要求される。
`query()` で内部のデータすべての総積を $O(1)$ で求められる。

#sourcecode(```cpp
using T = pair<mint, mint>;
const T e = pair{1, 0};
#define op(a, b) \
  pair { a.first *b.first, b.first *a.second + b.second }
```)

#sourcefile(read("../Structure/swag.cpp"), lang: "cpp")
