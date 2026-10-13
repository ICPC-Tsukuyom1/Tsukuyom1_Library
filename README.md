# Tsukuyom1_Library

追加して～

## Verify

Library Checker、yukicoder、AOJの問題を使い、GitHub Actionsで自動Verifyできるようになっています

以下の条件をすべて満たすファイルに対し、PRまたはmainブランチへの変更をトリガーとして自動的に実行されます

- 拡張子 `.cpp` をもつ
- verifyフォルダ以下に存在する
- ファイルの一行目が `//@yosupo {問題id}`、`//@yukicoder {問題id}`、または `//@aoj {問題id}` となっている
  - Library Checker の問題idは `https://judge.yosupo.jp/problem/` の後に続く文字列です
  - yukicoder の問題idは `https://yukicoder.me/problems/no/` の後に続く数字列です
  - AOJ の問題idは `https://onlinejudge.u-aizu.ac.jp/problems/` の後に続く文字列です

## Expander

`./scripts/expander.py {cppファイル}` を実行することで、指定したcppファイルのインクルードを展開したコードを標準出力に出力します
オンラインジャッジに提出する際などにご利用ください


