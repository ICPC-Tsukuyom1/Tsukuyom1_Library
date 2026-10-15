# Tsukuyom1_Library

追加して～

## Verify

Library Checker、yukicoder、AOJの問題を使い、GitHub Actionsで自動Verifyできるようになっています

以下の条件をすべて満たすファイルに対し、PRまたはmainブランチへの変更をトリガーとして自動的に実行されます

- 拡張子 `.cpp` をもつ
- verifyフォルダ以下に存在する
- 行頭から始まる `//@yosupo {問題id}`、`//@yukicoder {問題id}`、または `//@aoj {問題id}` の行がある（出典ヘッダーが先頭にあるため、問題マーカーは一行目でなくて構いません）
  - Library Checker の問題idは `https://judge.yosupo.jp/problem/` の後に続く文字列です
  - yukicoder の問題idは `https://yukicoder.me/problems/no/` の後に続く数字列です
  - AOJ の問題idは `https://onlinejudge.u-aizu.ac.jp/problems/` の後に続く文字列です

## Expander

`./scripts/expander.py {cppファイル}` を実行することで、指定したcppファイルのインクルードを展開したコードを標準出力に出力します
オンラインジャッジに提出する際などにご利用ください。展開後も出典コメントは保持されるので、コメントを含めてコピーしてください。

## 出典URLとコンテストでの利用

出典ヘッダーの対象は、Git追跡ファイルのうち拡張子が `.cpp`、`.cc`、`.cxx`、`.c`、`.h`、`.hh`、`.hpp`、`.hxx`、`.ipp`、`.tpp` のC/C++コードだけです。拡張子は大文字・小文字を区別します。Verifyやテンプレートのコードも対象ですが、Typst文書、Markdown、スクリプト、CI設定などには付けません。

対象コードは次の1行で始まります。`<path>` はリポジトリルートからの各ファイルのパスです。

```cpp
/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/<path> */
```

コピー時はこのURLコメントを保持してください。

**URLの記載やCIの成功だけでは、コンテスト開始前のWeb公開やルール適合を保証できません。** [AtCoderの生成AI利用ルール](https://info.atcoder.jp/entry/llm-rules-ja)など、参加する大会の最新ルールを確認してください。未公開ブランチやローカル変更は公開済みコードとして扱わず、PRで追加したコードもmainへのマージ・公開後に利用してください。大会中の生成AIによる修正を許可する仕組みではありません。

`main` のURLは更新・移動で参照内容が変わります。コンテスト前に利用する公開コミットを確定し、必要に応じてGitHubのpermalink（`blob/<commit SHA>/<path>`）も提出に添えることを推奨します。

### 追加・移動時の手順

リポジトリルートで以下を実行します。対象はGit追跡ファイルだけなので、新規ファイルやrenameは先に `git add` してください。

```sh
python3 -B scripts/source_urls.py fix
python3 -B scripts/source_urls.py check
```

`fix` は対象C/C++コードの管理ヘッダーを追加・更新します。差分を確認し、ヘッダーの変更も `git add` してください。対象外の拡張子にヘッダーは要求せず、例外マニフェストも使用しません。生成PDF、ビルド成果物、依存パッケージ、別worktreeは対象に含めません。

PRとmainへのpushでは、`source-urls` ジョブが単体テストと出典検査を実行します。CIは自動修正・commit・pushを行いません。ブランチ保護のrequired checkへの設定を推奨しますが、これはリポジトリ管理者による別途設定が必要です。

## 印刷用PDF

```sh
./docs/build.sh
```

原本のヘッダー検査に成功した後、Git追跡ファイルを一時ディレクトリにコピーし、対象C/C++コードの検証済みURLブロックコメントだけを除去してTypstでコンパイルします。既存の出典・ライセンスコメントは保持し、原本・Git indexは変更しません。成功したPDFのみ `docs/main.pdf` に配置し、開始時・失敗時には古いPDFを残しません。一時ファイルは終了時に削除します。Python 3とTypst、および文書で使用するフォントが必要です。

印刷用PDFは出典ヘッダーを省くため、AtCoder提出のコピー元には利用せず、ヘッダー付きの原本またはExpanderの出力を利用してください。`docs/watch.sh` は従来どおり直接Typst watchを実行し、掲載コードの出典ヘッダーを除去しません。出典URL行なしのPDFは、自分で印刷してコンテストに持ち込む用途向けで、CC0のライセンス文面は含みません。

## ライセンス

本リポジトリは [CC0 1.0 Universal](LICENSE) のもとで公開します。CC0は著作権表示を要求しませんが、このリポジトリでは出典URLコメントをコピー時に保持してください。AtCoder等の出典提示ルールはライセンスと別に適用されます。第三者由来の素材は元のライセンス条件に従ってください。


