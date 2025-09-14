#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== ハッシュ/乱数

=== 列 (Rolling Hash)

十分大きな素数 $P$ 、それ未満の値 $x$ を利用し、$"Hash"(A) = sum (A_i x^(N-i)) mod P$

- 一致判定
- (長さが既知の場合) 列同士の加算
- (長さが既知の場合) 列の連結
    - 列A, Bをこの順で連結するとき、$"Hash"(A+B) = (A * x^(|B|) + B) mod P$

を高速に計算可能

また、列同士の(要素ごと)XORを利用したい場合、加算の代わりにXORを、乗算の代わりにNim productを利用する (Nimber)
Nim productは $a times.circle b = "mex" { (a times.circle b') plus.circle (a' times.circle b) plus.circle (a' times.circle b) | a' < a, b' < b }$ で表される演算であり、Nimberは交換・結合法則を満たす

=== 集合 (Zobrist Hash)

各値にランダムな数を割り当て、要素の総XORをハッシュとする

- 一致判定
- insert/erase
    - 対象をXOR
- 集合同士のXOR

を高速に計算可能

=== 多重集合

各値にランダムな値を割り当て、その総和のmodをハッシュとする

Pとして $2^61-1$ など大きな素数を使うとよい (衝突確率 $1/P$) が、面倒であれば $2^64$ でも問題ない (衝突確率 $1/(2^(64-log_2 N))$)
