#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== fps

形式的冪級数。`poly` を継承し、級数演算 (`log` / `exp` / `sqrt` / `pow`) を追加する。

注: 戻り値が `poly<mint>` となる演算 (`*` / `+` / `-` / `pre` / `inv` / `diff` / `integral` など) は、その結果の静的な型が `poly<mint>` であるため、続けて級数演算を繋げることはできない。繋げたい場合は `fps<mint>(...)` で包む。

#sourcecode(```cpp
auto a = fps<mint>(f * g).log(n);    // (f * g).log(n) は不可
auto b = fps<mint>(f.pre(n)).exp(n); // f.pre(n).exp(n) は不可
```)

#sourcefile(read("fps.cpp"), lang: "cpp")
