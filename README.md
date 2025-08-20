# Tsukuyom1_Library

追加して～

## Verify

Library Checkerの問題であれば、GitHub Actionsで自動Verifyできるようになっています

以下の条件をすべて満たすファイルに対し、PRまたはmainブランチへの変更をトリガーとして自動的に実行されます

- 拡張子 `.cpp` をもつ
- verifyフォルダ以下に存在する
- ファイルの一行目が `//@yosupo {問題id}` となっている
  - ただし、問題idは `https://judge.yosupo.jp/problem/` の後に続く文字列です