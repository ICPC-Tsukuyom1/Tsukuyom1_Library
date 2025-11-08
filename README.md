# Tsukuyom1_Library

追加して～

## Verify

Library Checkerの問題であれば、GitHub Actionsで自動Verifyできるようになっています

以下の条件をすべて満たすファイルに対し、PRまたはmainブランチへの変更をトリガーとして自動的に実行されます

- 拡張子 `.cpp` をもつ
- verifyフォルダ以下に存在する
- ファイルの一行目が `//@yosupo {問題id}` または `//@yukicoder {問題id}` となっている
  - ただし、問題idは `https://judge.yosupo.jp/problem/` の後に続く文字列、または `https://yukicoder.me/problems/no/` の後に続く数字列です

## Expander

`./scripts/expander.py {cppファイル}` を実行することで、指定したcppファイルのインクルードを展開したコードを標準出力に出力します
オンラインジャッジに提出する際などにご利用ください

## Verify Checker

`./scripts/check_verification.py` を実行することで、verifyが設定されていないソースファイルを検出できます
