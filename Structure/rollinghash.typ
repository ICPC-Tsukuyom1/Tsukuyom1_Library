#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Rolling Hash

*なにこれ*

Rolling Hash は、文字列一致判定を高速に行うアルゴリズムである。

*使い方*

*宣言*

#sourcecode(```cpp
RollingHash rh(s);
```)

文字列 s を渡すことで、各iに対して [0, i) のHash関数の結果を構築する。

*get*

#sourcecode(```cpp
rh.get(l, r)
```)

[l, r)区間の文字列のハッシュ値を取得する。

#sourcefile(read("../Structure/RollingHash.cpp"), lang: "cpp")
