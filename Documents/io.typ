#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 入出力

=== 高速化

#sourcecode(```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
#define endl '\n'
```)

=== マニピュレータ

- `boolalpha` : boolを文字列として入出力する
- `uppercase` : 大文字で出力
- `dec`, `hex`, `oct` : それぞれ10/16/8進法
- `showbase` : ↑に基数プレフィックスを付与
- `fixed`, `scientific` : 小数/指数表記で入出力
