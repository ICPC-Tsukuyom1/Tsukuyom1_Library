#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== bit演算

=== 部分集合列挙

`rrep(b, 0, 1<<n) rep(i, n) if((b>>i)&1) insert(A[i])` のような動作をする。

#sourcecode(```cpp
for(int bit = A; ; bit = (bit-1) & A) {
  f(bit);
  if (!bit) break;
}
```)

=== 上位集合列挙

`A` を部分集合としてもつ集合を列挙する。

#sourcecode(```cpp
for (int bit=A; bit < (1<<n); bit=(bit+1)|A) {
  f(bit);
}
```)

=== next_combination

`popcount(b) == k` なる `b` を列挙する。

#sourcecode(```cpp
int next_combination(int sub) {
  int x = sub & -sub, y = sub + x;
  return (((sub & ~y) / x) >> 1) | y;
}
for (int bit = (1<<k)-1; bit<(1<<n); bit=next_combination(bit)) {
  f(bit);
}
```)
