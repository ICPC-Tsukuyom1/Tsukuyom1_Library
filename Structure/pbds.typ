#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== pbds

インデックスアクセス可能なSetとして `Tree` 、MultiSet版の `MultiTree` 、多少高速なHashMapとして `FastMap` を追加します。

- `Tree::find_by_order(i)` : (0-indexedで) i番目のイテレータを返します。
- `Tree::order_of_key(x)` : xを挿入した際、(0-indexedで) どのインデックスに配置されるかを返します。

また、`FastMap` はHash関数を変更できます。以下のように、operator()を実装したクラスを実装し、templateの第三引数として渡してください。

#sourcecode(```cpp
struct chash {
    ull operator()(ll X) const {
        ull x = X;
        x ^= rotr(x, 23) ^ rotr(x, 47);
        x ^= x >> 13;
        x ^= x << 37;
        x ^= x >> 21;
        return x;
    }
};
```)

#sourcefile(read("../Structure/pbds.cpp"), lang: "cpp")