# Verify専用Fast I/O

`fastio.hpp` はyosupoのverifyでのオンライン提出・速度比較用I/Oです。ライブラリ本体やPDFには含めません。
yosupoのverifyはFast I/Oに統一し、AOJ・yukicoderのverifyは従来のI/Oを使用します。

```cpp
#include "../../../template.cpp" // verify/yosupo/<category>/ から
#include "../../fastio.hpp"

FastIn in;
FastOut out;

int main() {
  ll a, b;
  in >> a >> b;
  out << a + b << '\n';
}
```

## 対応・利用条件

- `fread` / `fwrite` を使う64KiBバッファ。`FastIn<N>` / `FastOut<N>`でサイズ変更可能。
- `template.cpp`を先にincludeしてください。
- 64bit以下の標準整数型（入力の`bool`を除く）、文字、文字列に対応。出力は`bool`にも対応。128bit整数は非対応です。
- 整数は対象型の範囲内の有効な10進トークンが前提。先頭`+` / `-`、符号付き整数の最小値を扱えます。オーバーフロー検査はしません。
- 文字と文字列の入力ではASCIIの空白（バイト値32以下）を読み飛ばします。浮動小数点・コンテナ・BigInt自体の入出力は未対応です。
- `in.read(x)`は成否を返し、`in >> x`の成否は`if (in)`で確認できます。最後のトークンには改行不要です。
- `out.write(x)` / `out.put(c)`、`out.flush()`も利用可能。終了時に自動flushし、明示flushはC stdioのバッファもflushします。
- 同じストリームで`cin` / `cout`や他のstdio操作と混在させないでください。
- 入力は`stdin`、出力は`stdout`固定です。通常ファイルからのリダイレクトとパイプの両方に対応します。

## Verify・提出

- `yosupo/io/many_aplusb.cpp`: 64bit整数の大量入出力。
- `yosupo/data_structure/point_add_range_sum.cpp`: セグ木のverifyも同じFast I/Oを使用します。
- `mint`は`ll`で読んでから構築・代入し、従来の正規化を維持します。出力は整数値の`.x`を使用します。
- yosupoの幾何問題は整数入力が保証されるため、`ll`で読んでから座標へ代入します。

既存の`//@yosupo`によるworkflowが各ファイルを検出します。提出時は`fastio.hpp`を含め、同じコードを展開します。
既存expanderには絶対パスを渡してください。例えばリポジトリのルートから以下を実行できます。

```sh
python3 - <<'PY' > /tmp/submission.cpp
from pathlib import Path
from scripts.expander import process_file
p = Path('verify/yosupo/data_structure/point_add_range_sum.cpp').resolve()
print(process_file(str(p), str(p.parent)))
PY
g++ -std=c++20 -O2 /tmp/submission.cpp -o /tmp/submission
```

## テスト

```sh
python3 verify/tests/test_fastio.py --sanitize
```

境界値、EOF、1 / 7 / 20 / 21 / 65536バイトのバッファ、長い文字列・先頭ゼロ、明示・終了時flushをPythonの期待値と照合します。
GitHub Actionsの`fastio-tests`でも同じテストを実行します。

## 速度比較

整数入力はバッファ内で走査し、little-endianでは8桁を64bit演算でまとめて変換します。短い整数・バッファ境界・big-endianでは通常の桁処理へ戻ります。整数出力は十分な空きがあれば出力バッファへ直接変換し、中間コピーを省きます。

Many A+Bの最速提出には十進文字列を直接加算する問題専用実装もあるため、実行時間だけでなく提出ソースも確認してください。`cin` / `cout`という名前でも、独自I/Oへマクロ置換されている場合があります。

正答・coverageのためのCI実行時間は、ベンチマークとして扱いません。
同じコンパイラ・`-O2`・入力ファイルを使い、coverageなしで実行時間を比較してください。
`cin` / `cout`版との比較では`sync_with_stdio(false)`・`cin.tie(nullptr)`も有効にします。
ローカル計測はオンラインjudgeとはCPUやI/O条件が異なります。オンラインでも同じ提出コードを用い、同じケースの時間を比較します。
