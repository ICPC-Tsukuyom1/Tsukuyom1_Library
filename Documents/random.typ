#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== ランダム

=== 乱数生成

#sourcecode(```cpp
// 半開区間 [l, r) から一様ランダムに整数を返す
ll rnd(ll l, ll r) {
	static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
	return uniform_int_distribution<ll>(l, r - 1)(gen);
}
```)

=== 列のシャッフル

$O(n)$

#sourcecode(```cpp
// 使う都度エンジンを用意して渡す
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
shuffle(all(v), rng);
```)

=== 列と木の対応 (プリューファー列)

$1$ から $n$ の値による長さ $n-2$ の列 $P$ と $n$ 頂点のラベル付き木 $T$ の間に一対一対応がある。

プリューファー列を一様に選ぶと、ラベル付き木（Cayley 木）を一様に生成できる。Cayley 木の典型高さは $\Theta(\sqrt{n})$ である。

「葉のうちもっとも頂点番号の少ないもの」を順に取り除き、その親を列に追加していくことでラベル付き木からプリューファー列を得られる。

逆に、プリューファー列からラベル付き木を復元するには、次の手順に従う。

- 頂点 $i$ の次数は、プリューファー列に $i$ が現れる回数に $1$ を加えたもの。これを `d[i]` とする。
- 優先度付きキュー（最小ヒープ）に、`d[i] == 1` の頂点を全て入れる。
- 次を列の先頭から順に $n-2$ 回行う。
  - ヒープから最小の葉 `u` を取り出し、次の要素 `p = P[j]` と辺 `(u, p)` を結ぶ。
  - `d[u]--, d[p]--`。`d[p] == 1` になったらヒープに入れる。
- 残った $2$ 頂点を結ぶ。
