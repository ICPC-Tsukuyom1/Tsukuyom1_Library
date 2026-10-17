# Tsukuyom1_Library 問題点一覧（検証済み版）

調査対象: `C:\Users\oxojo\Tsukuyom1_Library` (ICPC-Tsukuyom1_Library)

- 調査方法: 全 `.cpp` / `.typ` / ワークフロー / スクリプトの静的レビューに加え、`g++ 15.2.0 (MinGW-w64)` による**実コンパイル・実実行・総当たり照合**で検証。
- 凡例: **✅ = コンパイルまたは実行で再現確認した** / **⚠ = コード読解に基づく（未テストまたは条件付き）**
- **状態列（本更新で追加）**: **修正済み** = 現行 main で解消 / **一部修正** = 緩和済み・記述が現状と不一致 / **未修正** = 現状でも再現 / **該当なし** = 記述自体が誤り / **要確認** = 静的には判定不能
- 前版に含まれていた誤検出（false positive）は [§10](#10-前版からの撤回誤検出だった項目) にまとめて撤回した。
- 更新履歴:
  - 初版: commit `4412a56` 時点（PR #159 マージ後）
  - **本版: main `eec8998` 時点（PR #160 幾何修正 / #161 幾何 6 機能追加 のマージ後）に全項目を現行コードと再照合し、状態を付与**
  - **追補: main `53bc47c` 時点（PR #163 fps リファクタ / #164 fps 性能改善 のマージ後）に fps 関連項目を再照合し、状態を更新**

---

## 目次

1. [コンパイルできない / 単体でコンパイル不能なファイル](#1-コンパイルできない--単体でコンパイル不能なファイル)
2. [メモリ安全性 / 未定義動作](#2-メモリ安全性--未定義動作)
3. [正当性のバグ（ロジック）](#3-正当性のバグロジック)
4. [スタックオーバーフロー（再帰）](#4-スタックオーバーフロー再帰)
5. [パフォーマンス / デッドコード / リーク](#5-パフォーマンス--デッドコード--リーク)
6. [ファイル結合時の衝突（根本設計問題）](#6-ファイル結合時の衝突根本設計問題)
7. [ドキュメントの欠陥](#7-ドキュメントの欠陥)
8. [CI / スクリプト / リポジトリ衛生](#8-ci--スクリプト--リポジトリ衛生)
9. [命名の不統一 / テストカバレッジ](#9-命名の不統一--テストカバレッジ)
10. [前版からの撤回（誤検出だった項目）](#10-前版からの撤回誤検出だった項目)
11. [優先度付き修正リスト](#11-優先度付き修正リスト)
12. [追加が望ましいライブラリ（機能拡充候補）](#12-追加が望ましいライブラリ機能拡充候補)

---

## 1. コンパイルできない / 単体でコンパイル不能なファイル

| # | 位置 | 問題 | 状態 |
|---|---|---|---|
| 1 | ✅ `Graph/Bellman-Ford.cpp:18,24` | 関数が18行目で閉じ、19–23行目が名前空間スコープに露出（`for`/`return`）。余分な `}` が24行目。**一度もコンパイルされたことがない。** | 修正済み |
| 2 | ✅ `Graph/Bellman-Ford.cpp:6,10,15,20` | `INF` を使用するが、このファイルにも `template.cpp` にも定義が無い（グローバル `INF` は `mincostflow.cpp:4` のみ）。include 順依存。 | 修正済み |
| 3 | ✅ `Graph/Bellman-Ford.cpp:14-17` | 8–13行目と同じ緩和パスが重複し、`V+1` 回実行してしまう。 | 修正済み |
| 4 | ✅ `Geometry/circleTangents.cpp:7` | `i.rotate(theta, c.c)` は2引数。2次元 `Point::rotate`（`Point.cpp:25`）は1引数のみ。 | 修正済み |
| 5 | ✅ `Geometry/Polygon_cut.cpp:9` | `lineInter(...)[1]`。戻り値は `std::pair<bool,Point>` で `operator[]` が無い（正しくは `.second`）。 | 修正済み |
| 6 | ✅ `Structure/kd-tree.cpp:50-51` | `l->get(...)` / `r->get(...)`。メンバは `foreach`（`:41`）で `get` は存在しない。 | 修正済み |
| 7 | ✅ `Geometry/ccInter.cpp:6` | `inf` は `clInter.cpp:3` でしか定義されず、単体では未宣言。 | 修正済み |
| 8 | ✅ `Graph/twosat.cpp:18` | `SCC` を使用するが include / コメントが無く単体で未宣言。 | 未修正 |
| 9 | ✅ `Graph/directed-mst.cpp:14-15` | 依存 `SkewHeap` / `UFRollback` がコメントのみで未 include。 | 未修正 |
| 10 | ✅ `Math/binomial-coefficients.cpp:2` | 裸の `mint`。ライブラリ全体にグローバル `mint` 定義が無い（`matrix.cpp:3`、`solveLinear.cpp:3,37` も同様）。 | 未修正 |
| 11 | ✅ `Geometry/Point3D.cpp:2` × `Point.cpp` | 両方が `struct Point` を定義。同時 include で再定義エラー。 | 修正済み |
| 12 | ✅ `Graph/{Bellman-Ford:2, Kruskal:4, directed-mst:4}` + `rerooting.cpp:3` | 4系統の `struct Edge` が衝突。 | 未修正 |
| 13 | ✅ `Graph/rerooting.cpp:10,12-13,19,21-26,32-41` | `V` / `E` / `ee` / `op` / `put_edge` / `put_vert` を未定義のまま使用。`rerooting.typ` のマクロ前提が正だが、**コンパイル不能なファイルとして `.cpp` 公開されている**。 | 未修正 |

> 補記: #7 は `inf` の定義が `Point.cpp:6`（`const ld inf = numeric_limits<ld>::infinity();`）へ移り、`Point.cpp` を include する通常構成で解決。`ccInter.cpp:2` に `// depends on: Point, commonTangents` を明記。

## 2. メモリ安全性 / 未定義動作

| # | 位置 | 問題 | 状態 |
|---|---|---|---|
| 14 | ✅ `Strings/SuffixArray.cpp:6,12` | `vl x(all(s))` が符号付き `char` をそのまま昇格。`>=0x80` のバイトで `ws[x[i]]++` が負添字 → クラッシュ（`_GLIBCXX_DEBUG` で確認）。 | 修正済み |
| 15 | ✅ `Structure/BIT.cpp:7,11` | コンストラクタで `N=N_+1` の後 `rep(i,N) data[i+1]=v[i]` → `v[sz(v)]` を読む（`BIT(vector)` でアボート）。 | 修正済み |
| 16 | ✅ `Structure/dualsegtree.cpp:35-39` | `get(i)` に `i<n` のチェックが無く `i==n` で `2n` 添字。 | 一部修正（`assert` 追加のみ。`NDEBUG`（verify 既定）では依然 OOB） |
| 17 | ✅ `Structure/wavelet-matrix.cpp:33` | `bit_width(values.size() - !values.empty())` が空入力で `size_t` アンダーフロー → `lg=64` → `1LL<<64` は UB。 | 修正済み |
| 18 | ✅ `Structure/LiChaoTree.cpp:12-13` | `ll n;` が既定コンストラクタ `LCTree() {}` で未初期化。 | 修正済み |
| 19 | ✅ `Structure/LiChaoTree.cpp:18` | `while (sz(x)<n) x.push_back(x.back())` が空 `x` で `back()` = UB。 | 修正済み |
| 20 | ✅ `Structure/LiChaoTree.cpp:56-58` | `query(t)` が `t > max(x)` で `seg[2n]` を参照（定義域チェック無し、未記載）。 | 修正済み |
| 21 | ✅ `Structure/SparseTable.cpp:17` | `fold(l,l)` で `__lg(0)` = UB、かつ負添字読み。 | 一部修正（`assert(l<r)` のみ。`NDEBUG` では依然 UB） |
| 22 | ✅ `Structure/disjoint-sparsetable.cpp:23` | `fold(l,l)` で `__lg(l ^ r)` = `__lg(-1)`、クラッシュ。 | 一部修正（`assert(l<r)` のみ。`NDEBUG` では依然 UB） |
| 23 | ✅ `Structure/binary-trie.cpp:87-98` | `at(k)` に境界チェックが無く `k>=size()` で null 参照。 | 未修正（`bt.at(1)` を実測でクラッシュ確認） |
| 24 | ✅ `Math/fps.cpp:249-254` | `shift()` が空多項式で `rfact[n-1]`（`rfact[-1]`）を参照。 | 修正済み |
| 25 | ✅ `Math/fps.cpp:220-225` | `pow(0,0)` で `P res(0)` に `res[0]=1`。 | 修正済み |
| 26 | ✅ `Math/fps.cpp:197` | `sqrt()` が空で `(*this)[0]` を参照。 | 修正済み |
| 27 | ✅ `Math/BigInt.cpp:167-177` | `divmod()` に除数ゼロのガードが無く、`BigInt/0` でゼロ除算クラッシュ。 | 修正済み |
| 28 | ✅ `Math/binomial-coefficients.cpp:4-21,25` | `init(n)` が `pascal` を消去しない。`init(10)` → `init(5000)` の後 `com(4000,2)` で範囲外。 | 未修正 |
| 29 | ✅ `Math/golden_section_search.cpp:3,6` | 固定 `eps=1e-7`。最小値が巨大座標（例: `f=(x-1e18)^2`）だと `r-l` が縮まず**無限ループ**。 | 未修正（実測で停止） |
| 30 | ✅ `Geometry/area.cpp:4` | 空多角形でも `S[0]` を無条件参照。 | 修正済み |
| 31 | ✅ `Geometry/minEncloseCirc.cpp:5,13` | 空入力で `ps[0]` / 重複点で外心計算が縮退し NaN。 | 修正済み |
| 32 | ✅ `Geometry/diamConvex.cpp:6` | 空入力で `Q[0]` を参照。 | 修正済み |
| 33 | ✅ `Structure/swag.cpp:16-17` | `front()` / `back()` に空チェックが無い。 | 未修正 |
| 34 | ✅ `Structure/hld.cpp:15` | `g[v].erase(find(all(g[v]), par[v]))`。8行目の契約（親→子のみ）だと `find` が `end()` を返し `erase(end())` = UB。 | 未修正（`_GLIBCXX_DEBUG` でアボート） |
| 35 | ✅ `Math/matrix.cpp:30` | `operator*=` が次元チェック無し。`A(2,3)*=B(2,2)` で範囲外アクセス。 | 未修正 |
| 36 | ⚠ `Math/modint.cpp:43` | `ll x * p.x % mod()` は `MOD > ~3e9` でオーバーフロー（`__int128` 未使用。`modula.cpp:2` は使用しており不整合）。 | 該当なし（`MOD` は `int` テンプレート引数で `≤2^31-1`。積は常に `ll` に収まる） |
| 37 | ⚠ `Math/modula.cpp:10-18` | `modlog` の `e*a%p` 等が素の `ll`。`p` が約 3e9 超でオーバーフロー。 | 未修正（`p` は `ll` 取り得る） |
| 38 | ⚠ `Math/extgcd.cpp:6` | `Y -= (A/B)*X` が大きい `|A|,|B|` で `ll` オーバーフロー。負入力では `%` の不変条件が崩れる。 | 未修正 |
| 39 | ⚠ `Math/floorsum.cpp:7,12` | `n*(n-1)/2*(a/c)` / `a*(n-1)+b` が `ll` オーバーフロー。 | 未修正 |
| 40 | ⚠ `Structure/BIT.cpp:32,43` | `1 << (__lg(N)+1)` のリテラル `1`。`N>=2^30` で負シフト / UB。 | 修正済み（`1LL << ...` 化） |
| 41 | ⚠ `Structure/LiChaoTree.cpp:5,41` | 「無限大」に `LLONG_MAX/4`、`1 << ub` も `int` シフト。`2.3e18` 以上の値は有限扱い。 | 未修正（`int` シフト残存） |
| 42 | ⚠ `Math/fps.cpp:151-158` | `operator()(T x)` が `mod` で還元せず素の整数を返す → オーバーフロー、体の値と不一致。 | 修正済み（#163 の modint 化で `poly<mint>::operator()` が `mint` を返すようになり解消） |
| 43 | ⚠ `Geometry/clInter.cpp:3` / `ccInter.cpp:6` | 「無限遠点」`-inf` は `LDBL_MAX/2` の**有限値**。算術と組み合わせるとゴミになる。 | 修正済み（`Point.cpp:6` で真の `infinity()`） |

## 3. 正当性のバグ（ロジック）

| # | 位置 | 問題 | 状態 |
|---|---|---|---|
| 44 | ✅ `Graph/flow.cpp:56` | `max_flow(s,s)` が無限ループ（`find(s,s,INF)` が毎回 `INF` を返す）。 | 未修正（実測でハング） |
| 45 | ✅ `Structure/segtree.cpp:34-46` | `max_right(f)` が `[0,N)` ではなくパディング後の `[0,next_pow2(N)]` の添字を返す（`N` を保持していない）。 | 未修正（`N=3` で `4`） |
| 46 | ✅ `Structure/hld.cpp:32-44` | `queryPath` は非可換モノイドで `u→v` の順にならない（`queryPath(u,v)==queryPath(v,u)`）。 | 未修正 |
| 47 | ✅ `Math/matrix.cpp:27-33` | `operator*=` が結果配列を差し替えるがメンバ `m` を更新しない → 以降の次元が崩れる。 | 未修正 |
| 48 | ✅ `Math/fps.cpp:7-8,48-55,89-103,174-177` | `set_mod()` が実質無効。継承した `vector<T>` のコンストラクタが `mod` / `root` を既定 `998244353` / `3` に戻す。 | 該当なし（#163 で `FPS<T>::set_mod` を廃止。mod は `modint<0>::set_mod`、原始根は `convolution(a, b, g)` の引数に分離。ただし `poly::operator*` は `g = 3` 固定のため、原始根 3 以外の NTT 素数では `convolution` を直接使う必要あり） |
| 49 | ✅ `Math/bitwise_xor_convolution.cpp:18` | `T iv = T(1)/sz(a);` が `T=ll` で整数除算（`>1` で0）→ 全ゼロ。 | 未修正 |
| 50 | ✅ `Math/binomial-coefficients.cpp:19` | `inv[i]=inv[i-1]/i` が1要素につき1回逆元計算 → `O(n log p)`。`n>=p` で静かに誤答。 | 未修正 |
| 51 | ⚠ `Math/binomial_coefficients.cpp:14` | `finv[n]=fac[n].inv()` が `n<mod` 前提。`n>=mod` で `inv()` の assert / 0 除算。 | 未修正 |
| 52 | ⚠ `Math/LucasBinom.cpp:5,10-13` | 既定引数 `Mint::mod()-1` が `mod` 長の配列を確保（`998244353` で GB 級、実用不可）。`modint<0>` 未設定時は `%0`。 | 未修正 |
| 53 | ⚠ `Math/modula.cpp:10-18,42` | `modlog` は `gcd(a,p)=1` 前提、`modinv` は素数前提。前提が未記載で合成数で静かに誤答。 | 未修正 |
| 54 | ⚠ `Math/FastFactorize.cpp:4-18` | `pollard` の失敗処理が無く `n` を返すと無限再帰の恐れ。`fac(0)` は `modmul(x,x,0)` で `%0`。`Euler_phi(0)` も同様。 | 未修正 |
| 55 | ⚠ `Graph/SCC.cpp:42-49` | 縮約 `dag` に重複辺の除去が無い（多重辺がそのまま）。下流の DP が誤る。 | 未修正 |
| 56 | ✅ `Geometry/isconvex.cpp:6-7` | 空・3点未満の多角形で `true`。自己交差の星形も `true`。 | 修正済み（`n<3` で `false`、全周回角判定を追加） |
| 57 | ✅ `Geometry/clInter.cpp:5-14` | `dd` が符号付きなのに `sign(dd-c.r)` で符号を無視。中心が負側で `sqrtl(負)` = NaN。 | 修正済み |
| 58 | ✅ `Geometry/ccInter.cpp:11` | 同心円 / 零半径で `d=0` のゼロ除算、`acosl` 未クランプで NaN。 | 修正済み |
| 59 | ✅ `Geometry/commonTangents.cpp:9,26,10-11,17,29` | ガード `Δr<=d+EPS` 等が効かず `sqrtl(負)` = NaN。接点で `h==0` → ゼロ長の「線」。 | 一部修正（NaN は解消。接点でゼロ長 `Line` が残る） |
| 60 | ✅ `Geometry/lineInter.cpp:5` | 平行 / 共線で `{1,(0,0)}` という偽の交点（原点が実頂点として混入し得る）。 | 修正済み（`{0,(0,0)}` を返す） |
| 61 | ✅ `Geometry/circumcircle.cpp:5-6` | `b.cross(c)` が共線 / 重複点で 0 → 除算で inf / NaN。 | 修正済み（共線時 `Circle(Point(), inf)`） |
| 62 | ✅ `Strings/KMP.cpp:12-14` | 空パターンで偽の解の列を返す（正解は `|s|+1`）。 | 未修正（`"abc"` で `[1,2,3]`） |
| 63 | ⚠ `Math/solveLinear.cpp:50` | `while (a[i][j].x==0) j++;` に `j<m` の上限が無い。 | 未修正 |
| 64 | ⚠ `Math/fps.cpp:165-170,188-193` | `integral` / `log` が次数 `mod` 到達や空系列で `modinv(0)` / 負オフセット。 | 一部修正（#164 で `integral` は 1..n の逆元表を O(n) 構築し `n < mod` を assert。空系列 `log` と `n >= mod` の破綻は残存） |
| 65 | ⚠ `Structure/weightedunionfind.cpp:7,22` | `find` / `size` が `int`、`n` は `ll`。`n>2^31` で切り詰め。 | 未修正 |
| 66 | ⚠ `Structure/binary-trie.cpp:62,70` | `erase` が葉の `cnt=0` にして**重複を全消去**（`insert` / `count` は重複を数える）。 | 未修正 |
| 67 | ⚠ `Structure/RollingHash.cpp:14` | `S[i]` が符号付き `char`。`>=128` で不一致。`base=150` 固定で非乱数。 | 未修正 |
| 68 | ⚠ `Graph/Kruskal.cpp:12-13` | 同コスト辺の順序が非決定的（`std::sort` は不安定）。MST コストは不変だが返る辺集合は実行ごとに変わる。 | 未修正 |
| 69 | ⚠ `Graph/topological.cpp:13-22` | 閉路の検出が無く、部分順序を返してエラー信号も無い。 | 未修正 |
| 70 | ⚠ `Graph/twosat.cpp:22` | 充足不能が `{}` で表現され `N==0` と区別できない。 | 未修正 |

> 注: `Math/matrix.cpp:54-75` の `det()` は `Matrix<ll>` では整数除算で誤る（体を仮定）。`Math/modint` の `inv()` / `Math/modula` の `modinv` は素数 MOD 前提。

## 4. スタックオーバーフロー（再帰）

CI が `ulimit -s unlimited` を付けるため露見しにくいが、実ジャッジ / `run.sh` では落ちる。✅ 実測で `0xC00000FD` を確認:

- **未修正** `Graph/flow.cpp:36-50`（Dinic `find`、パス 10^6 ノードで落ちる）
- **未修正** `Graph/SCC.cpp:15-26`
- **未修正** `Graph/LowLink.cpp:16-36`
- **未修正** `Graph/lca.cpp:10-16`（パス約 5万〜10万で落ちる）
- **未修正** `Graph/Centroid-Decomposition.cpp:20-34`（生の木の深さに比例）
- **未修正** `Graph/rerooting.cpp:14,31`（約 5万で落ちる）
- **未修正** ⚠ `Structure/hld.cpp:17,27`、`Structure/skew-heap.cpp:17-23`（深さ制限なし `merge`）
- **未修正** ⚠ `Graph/maxMatching.cpp:9-24`、`Graph/hopcroftKarp.cpp:9`（理論上のみ、実測では非再現）

## 5. パフォーマンス / デッドコード / リーク

- **未修正** `Structure/kd-tree.cpp:31-32` — `new` でデストラクタ無し → **全面リーク**。`function<T(T,T)> op` をノード毎に保持。
- **未修正** `Structure/binary-trie.cpp:31,67` — `new` でリーク。
- **未修正** `Structure/skew-heap.cpp:25` — `pop` がノードを捨てる（リーク）。
- **未修正** `Graph/directed-mst.cpp:17,28,34` — `new H` が O(E) リーク。
- **未修正** `Structure/dynamic-{segtree,dualsegtree,lazysegtree}.cpp:4` — グローバル `alloc_*` が解放不能（改名済みだが性質は同じ）。常に両子を確保し、読み取りクエリでも木全体が実体化。
- **修正済み** `Math/ntt.cpp` — NTT 長を必要量以上の最小の 2 冪に変更（#163。旧 `Math/fps.cpp:33` は必要量の 2 倍を確保していた）。
- **修正済み** `Math/poly.cpp` の `integral` — 係数ごとの逆元 `O(n log mod)` を O(n) の逆元表に（#164。旧 `Math/fps.cpp:168`）。`binomial` 系は別項（#50）。
- **修正済み** ⚠ `Math/fps.cpp:105-115` — `%=` / `div_mod()` は `*this` を破壊しない（`operator/`/`operator-` は const、`div_mod` は複製を使用）。
- **一部修正** `Graph/LowLink.cpp:5,9` / `Graph/maxMatching.cpp:4,72` — `LowLink` は値渡し＋メンバで二重コピー存続。`maxMatching` は参照引数で 1 回のみ。
- **未修正** ⚠ `Math/primroot.cpp:4-8` — `rnd` 呼び出し毎に `random_device` を生成。
- **未修正** ⚠ `Structure/LiChaoTree.cpp:14-15` — `const vector<ll>&` をメンバにコピーしてソート、座標の重複除去なし（`n` が最大 2 倍）。
- **未修正** ⚠ `Structure/SparseTable.cpp:5` / `disjoint-sparsetable.cpp:5` — トリム無しの `n×log n`。
- **一部修正** `Graph/flow.cpp:6,14` — `isrev` / `idx` が未読。/ `Graph/directed-mst.cpp:21` `comp` 未使用で即シャドー。/ `Graph/Centroid-Decomposition.cpp:41` 常に真。/ `Structure/dynamic-lazysegtree.cpp:19` ローカル `m` がメンバを隠蔽（スコープ内で無害）。なお `Graph/LowLink.cpp:4` の `n` は現在使用されている。
- **一部修正** `Math/fps.cpp` の `T rev`（`rev()` の隠蔽）と `sz`（マクロの隠蔽）は #163 で解消。`Math/matrix.cpp:67` の `T vv` が型 `vv` を隠蔽は未修正（偶然動作）。
- **未修正** ルート `io.cpp`(181行) / `dump.cpp`(8行) / `LIS.cpp`(14行) は**完全な孤児**（include / `.typ` / verify すべてゼロ）。`io.cpp:2-9` は `template.cpp:21-28` の `chmax`/`chmin` を二重定義。`io.cpp:175-181` は既定で `fixed`+`setprecision(16)` に変更（`chapter.typ` は 12 と記載）。

## 6. ファイル結合時の衝突（根本設計問題）

各 `.cpp` は include 展開で 1 つの翻訳単位に連結される前提だが、名前空間スコープが衝突している。

- **未修正** ✅ `Structure/swag.cpp:3` — `#define get(v) ...` がグローバル漏洩。`kd-tree` / `LiChaoTree` / `std::get` を破壊する。**ディレクトリ内で最も危険な 1 行。**
- **修正済み** ✅ `Structure/dynamic-{segtree,dualsegtree,lazysegtree}.cpp:4` — グローバル `alloc` が `alloc_seg` / `alloc_dual` / `alloc_lazy` に改名され衝突解消（解放不能という性質は §5 のまま）。
- **一部修正** マクロ `T/e/op`（segtree, SparseTable, disjoint-sparsetable）、`F/id/merge/apply`（lazy / dual）、`szt`（bitwise_*）が全空間に漏れ、相互排他。契約は各 `.typ` に記載されるようになったが、マクロ漏洩自体と `szt` の説明は未整備。
- **未修正** `Structure/pbds.cpp:4` — `using namespace __gnu_pbds;` が `tree` / `less` / `priority_queue` / `hash_map` を注入。
- **未修正** `Graph/hopcroftKarp.cpp:3` — ライブラリ唯一の自由関数 `dfs`。
- **未修正** `Math/primroot.cpp:4` — グローバル `ll rnd(ll,ll)`。
- **修正済み** `Math/binomial-coefficients.cpp:2` vs `FastFactorize.cpp:14` — 前者が `binom_fac` / `binom_inv` に改名され、`fac` 衝突解消。
- **未修正** `Math/binomial-coefficients.cpp:4` `void init(ll)` vs `io.cpp:175-181` `struct init`。
- **修正済み** `Geometry/Point.cpp:7` `typedef Point P` vs `closest_pair.cpp:3` `#define P Point` — `#define P` は削除され `Point` を直接使用。
- **未修正** `Math/matrix.cpp:3` / `solveLinear.cpp:3` が裸の `mint` を要求（ユーザ定義が必要）。
- **未修正** `Graph/mincostflow.cpp:4` の唯一のグローバル `const ll INF`（配置が他と不整合）。`Graph/mincostflow.cpp:2` は `<bits/extc++.h>` を include（GCC 内部ヘッダ、非移植）。

## 7. ドキュメントの欠陥

- **未修正** ✅ `Structure/segtree.cpp:6` コメント「構築 O(N log N)」は誤り（実際 `O(N)`）。
- **一部修正** `Math/binomial_coefficients.typ:5` — 依然 `read("binomial-coefficients.cpp")` で**死んだ側**を読む。ただし `binomial_coefficients.cpp` 側に URL ヘッダが追加された。
- **未修正** `Structure/weightedunionfind.typ:18,26` — 存在しない `connected` / `diff` を記載（実体は `find` / `merge` / `size` / `weight`）。`:5` にプレースホルダ `*なにこれ*`。
- **未修正** `Math/extgcd.typ:5` — 「`a x+b y=c` を解く」は嘘（返り値は gcd）。
- **修正済み** `Geometry/projection.typ:5` — `reflect` の説明が実装と一致。
- **修正済み** `Geometry/LineDistance.cpp:5` — **符号付き**距離（左側が正）である旨を明記。
- **修正済み** `Geometry/lineInter.typ:4` / `ccInter.typ:3-4` — 平行・非交差の返り値が実装と一致。`inf` が真の無限大である旨も明記。
- **未修正** `Graph/hopcroftKarp.typ` — 返り値が**2倍**であること（呼び出し側の `/2` 必須）が未記載。右側の `btoa` が非対称になり得る点も未記載。
- **未修正** `Graph/kruskal.typ:5` — `O(E log V)` は誤り（`O(E log E)`）。非連結時に全域**森**になる旨も未記載。
- **未修正** `Graph/PushRelabel.typ` — 使用法（`rcap`、再入不可）が皆無。
- **修正済み** `Graph/bellman-ford.typ` — ソース側のコンパイル不能が解消。
- **未修正** `Graph/{lca,LowLink,topological,twosat,Centroid-Decomposition}.typ` — 見出し＋1行のみ。`twosat.typ` に誤字。
- **未修正** `Graph/rerooting.typ` — `mint` 前提を書くが modint 依存が不明。
- **未修正** `Structure/dynamic-*.typ` など — `T/e/op/F/id/merge/apply` を事前 `#define` する契約が未記載。
- **未修正** `Structure/pbds.typ:14` — `ull` を使うが `template.cpp` に `ull` が無くコンパイル不可。
- **未修正** `chapter.typ:26` — `Math/modint.typ` を「Template」章に直接入れ、`Math/chapter.typ` は modint を含まない（レイヤリング違反）。
- **一部修正** `Math/{matrix,modint,binomial_coefficients}.typ` — ソースのみで散文ゼロ（`fps` は #163 で説明・注記を追加、`poly` / `ntt` の `.typ` も新設）。`Math/LucasBinom.cpp` は `.typ` 無し。
- **未修正** `Documents/Trigonometry.typ:6,9` — 加法定理が誤り（`cos x`、余弦の符号誤り）。`Documents/math.typ:48,56,58,64` — 係数・級数の誤り。`Documents/combination.typ:7,84,136` — 誤り / 誤字。`Documents/parallel-binsearch.typ:8` — 計算量が誤り。
- **一部修正** `README.md:3` — プレースホルダ「追加して～」は残存。`:20` の `expander.py` 用法は引数1つで一致するよう修正。verify の yukicoder トークン要件、カバレッジ系スクリプトは依然未記載。

## 8. CI / スクリプト / リポジトリ衛生

- **修正済み** ✅ `python scripts/source_urls.py check` が終了コード 0（`Verified: 97 files`）。`source-urls.yml` は緑。
- **未修正** ✅ ルートに `.gitignore` が無く、`scripts/__pycache__/source_urls.cpython-312.pyc` が追跡下。
- **一部修正** ✅ `run.sh` は `:1` のコメントが「実行」に修正済。100644・shebang なし・`-static`・`_GLIBCXX_DEBUG`、`./dist` / `./input` 未作成は健在。
- **未修正** ✅ `format.sh:3-4` は `dirname $0` 未クォート、`find . -name "*.cpp" | xargs` で無濾過（`verify` やビルド出力も対象）、CI から未呼び出し。
- **未修正** `.github/workflows/verify.yml:130,134` — yukicoder は `secrets.YUKICODER_TOKEN` 必須。fork PR で全滅。
- **要確認** `verify.yml:254-259` — カバレッジ artifact が 1 つも無い場合の `download-artifact` 挙動（0件ガード無し）。
- **未修正** `verify.yml:65` — `DIR` を代入前に `echo`。`:69` は Python セットアップ無しで generate。`:103` grep に重複排除 / ソート無し。`matrix.problem` を無害化せず shell へ埋め込み（インジェクション余地）。
- **未修正** `scripts/expander.py:16` — 循環 include 対策（訪問済み集合）が無く `RecursionError`、重複排除も無い。テスト無し・CI 未呼び出し。`:19` の `f"\n"`（不要な f プレフィックス）。
- **未修正** `scripts/aggregate_coverage.py:37-41` — `git ls-files` ではなく `root.rglob("*.cpp")` で未追跡ファイルまで拾う。
- **未修正** `.devcontainer/Dockerfile:2-3` — `g++` / `python3` / `typst` 等が無く、コンテナ内で `run.sh` / `format.sh` / docs / verify が一切動かない。`clang-format` はバージョン未固定。
- **未修正** `.vscode/settings.json` — `files.eol: "\n"` が無く、`core.autocrlf=true` 環境で `*.sh` が CRLF 化して Linux で壊れる。
- **未修正** 実行ビットが場当たり（`docs/build.sh` / `format.sh` / `expander.py` は 755、`run.sh` / `source_urls.py` は 644）。

## 9. 命名の不統一 / テストカバレッジ

- **未修正** `.cpp` ↔ `.typ` のベース名不一致が多数: `isinpolygon`↔`isinPolygon`、`LineDistance`↔`lineDistance`、`Bellman-Ford`↔`bellman-ford`、`Kruskal`↔`kruskal`、`SCC`↔`scc`、`Euler_phi`↔`euler_phi`、`BIT`↔`bit`、`BIT2d`↔`bit2d`、`RollingHash`↔`rollinghash`、`SparseTable`↔`sparsetable`、`UnionFind-rollback`↔`unionfind-rollback`、`binomial_coefficients.typ`↔`binomial-coefficients.cpp`。
- **未修正** 関数名の不一致 / タイポ: `circleTangents.cpp`→`circTangents`、`trincircle.cpp`→`trinCircle`、`ZAlgorithm.cpp`→`Zalgo`、`Structure/LiChaoTree.cpp`→`LCTree`。
- **未修正** セグメント木系の命名が 6 通り（`SegTree` / `LazySeg` / `DualSeg` / `DynamicSeg` / `DynamicLazySeg` / `DynamicDualSeg`）。
- **一部修正** **verify に include されていないライブラリ `.cpp` が 20 件**（旧 27 件）: `io.cpp` / `dump.cpp` / `LIS.cpp`、`Graph/{Bellman-Ford,flow,PushRelabel,Centroid-Decomposition,LowLink,topological}.cpp`、`Geometry/{LineDistance,Point3D,halfPlaneInter,isinConvexPolygon}.cpp`、`Math/{extgcd,garner,Euler_phi,binomial-coefficients}.cpp`、`Strings/KMP.cpp`、`Structure/{BIT2d,RollingHash}.cpp`。
  - 旧リストの `Geometry/{circleTangents,clInter,ccInter,commonTangents,isconvex,Polygon_cut,CircCircInter,CircPolyInter,trincircle}.cpp` は AOJ verify 追加などで解消。
  - 一方で `Geometry/{halfPlaneInter,isinConvexPolygon}.cpp` が新たに未カバー（#161 で追加したが verify 未整備）。§1〜§3 のバグが生き延びた原因。

## 10. 前版からの撤回（誤検出だった項目）

前版 `LIBRARY_ISSUES.md` の一部は過大な断定でした。今回の検証で**バグではない**と確認したもの:

- **PushRelabel の最大流が壊れている（前版 #21）** — 誤り。`H[u]=1e9` 番兵は必ず上書きされ範囲外にならない。Edmonds–Karp / Dinic と 20 万ケース以上一致（`_GLIBCXX_DEBUG` でも OOB 無し）。
- **mincostflow のダングリングポインタ（前版 #83,#86）** — 通常使用では再確保されず問題なし。
- **`maxMatching.cpp` の `gr[-1]`（前版 #20）** — 到達不能。20 万ケースで非再現。
- **`kd-tree.cpp:10` の `sum=e`（前版 #17）** — メンバ初期化順序的に問題なし（`e` は先に初期化済み）。
- **`lazysegtree.cpp` の即時 flush で `O(区間)` 劣化（前版 #47,#48）** — 依然 `O(log n)` で結果も正しい（300 ケース検証）。ただし `:27` が無関係ノードまで push するのは無駄。
- **`diamConvex.cpp` の剰余欠落（前版 #9）** — `%n` は存在し、アルゴリズムは 3000 多角形で総当たりと一致（空入力の `:6` のみ UB、本版で修正済み）。
- **`closest_pair.cpp:11` の erase（前版 #73）**、**`segInter.cpp` の set / onSegment 不整合（前版 #77）**、**`ccInter` が `commonTangents` を呼ぶ点（前版 #71 は性能問題のみ）**、**`CircPolyInter` の `arg` が `std::arg` を隠蔽（前版 #127）**、**`CircCircInter`/`CircPolyInter` の `fac` 衝突（前版 #126）** — いずれも実際にはバグではありません（オーバーロード / no-op）。
- **`SuffixArray.cpp` の `y[a+j]` 範囲外（前版 #18）** — 短絡評価により実測では再現せず。
- **`flow.cpp` の自己ループで `rev` が壊れる（前版 #82）** — Dinic は自己ループを走査しないため結果に影響なし（潜在的な脆さのみ）。
- **（本版で追加撤回）`Math/modint.cpp` の `ll` オーバーフロー（§2 #36）** — `MOD` は `int` テンプレート引数のため `2^31-1` を超えず、`x*x < 2^62` で `ll` に収まる。

## 11. 優先度付き修正リスト

> 本更新（main `eec8998` 再照合）を反映。解消済みの項目は「完了」へ移動した。fps 関連は main `53bc47c`（#163・#164 マージ後）で追記更新。

### 完了（本更新で確認）

- URL ヘッダ整備により `source_urls.py check` が pass（97 ファイル）。
- `Graph/Bellman-Ford.cpp` の波括弧・`INF`・`return`（§1 #1–3）。
- `Structure/kd-tree.cpp:50` の `get`→`foreach`（#6）、`Geometry/Polygon_cut.cpp:9` の `.second`（#5）、`Geometry/circleTangents.cpp:7` の 2 引数 `rotate`（#4）。
- 名前衝突: `Point3D` 改名（#11）、`alloc` 3 系統の改名（§6）、`fac`（§6）、`#define P` 削除（§6）。
- メモリ安全: `SuffixArray`（#14）、`BIT`（#15,#40）、`dualsegtree`/`wavelet-matrix`/`LiChaoTree`(#18–20)/`SparseTable`(#21)/`disjoint-sparsetable`(#22) のガード、`fps` 空ガード（#24–26）、`BigInt` ゼロ除算（#27）、`Geometry` 空入力（#30–32）、`inf` の真の無限大化（#43）。
- 幾何ロジック: `isconvex`(#56) / `clInter`(#57) / `ccInter`(#58) / `circumcircle`(#61) / `lineInter`(#60)。
- `Math/fps.cpp` の `%=` / `div_mod` の破壊（§5）。
- **（fps リファクタ / 性能改善 #163・#164 で追加解消）** `operator()` の非還元（#42）、NTT 長 2 倍（§5）、`integral` の `O(n log mod)`（#2 / §5）、`T rev`・`sz` の隠蔽（§5）、`fps.typ` の散文ゼロ（§7）。
- ドキュメント: `projection` / `LineDistance` / `lineInter` / `ccInter` / `bellman-ford`（§7）。

### 最優先（コンパイル不能 + メモリ安全）

1. `Graph/twosat.cpp:18` の `SCC` 依存を明示（#8）。
2. `Graph/directed-mst.cpp:14-15` の `SkewHeap` / `UFRollback` 依存を明示（#9）。
3. 裸の `mint`（`Math/binomial-coefficients.cpp:2`、`matrix.cpp:3`、`solveLinear.cpp:3,37`）を自己完結化（#10）。
4. `struct Edge`（`Bellman-Ford` / `Kruskal` / `directed-mst` / `rerooting`）の衝突解消（#12）。
5. `Graph/rerooting.cpp` の未定義マクロ依存（`V/E/ee/op/put_edge/put_vert`）を解消（#13）。
6. `Structure/binary-trie.cpp:87` の `at()` 境界チェック（#23）。
7. `Math/binomial-coefficients.cpp` の `init` で `pascal` を clear（#28）。
8. `Math/golden_section_search.cpp` の無限ループ（#29）。
9. `Structure/swag.cpp` の空 `front/back`（#33）、`Structure/hld.cpp:15` の `erase(end())`（#34）、`Math/matrix.cpp:27` の `operator*=` 次元と `m` 更新（#35,#47）。
10. `NDEBUG` で無効化される `assert` のみのガード（#16,#21,#22）を実ガードへ。

### 高（正当性）

11. `Graph/flow.cpp:56` の `max_flow(s,s)`（#44）。
12. ~~`Math/fps.cpp:7` の `set_mod` 無効（#48）、`:33` の NTT 長（§5）。~~ **完了**（#163・#164）。
13. `Math/bitwise_xor_convolution.cpp:18` の整数除算（#49）。
14. `Math/binomial-coefficients.cpp:19` の逆元 `O(n log p)`（#50）、`binomial_coefficients.cpp:15` の `n<mod` 前提（#51）。
15. `Math/LucasBinom.cpp` の既定引数確保（#52）、`modula` / `extgcd` / `floorsum` の前提・オーバーフロー（#37,#38,#39,#53）。
16. `Math/FastFactorize.cpp` の失敗処理（#54）。
17. `Geometry/commonTangents.cpp` の接点ゼロ長（#59）。
18. `Strings/KMP.cpp` の空パターン（#62）、`Structure/segtree.cpp` の `max_right` 添字クランプ（#45）、`Structure/hld.cpp` の `queryPath` 順序（#46）。
19. `Math/solveLinear.cpp:50`（#63）、`fps` integral/log（#64、#164 で一部修正）、`weightedunionfind` の `int`（#65）、`binary-trie` erase（#66）、`RollingHash` 符号（#67）、`Kruskal` 非決定（#68）、`topological` 閉路（#69）、`twosat` 不能表現（#70）、`SCC` 縮約の重複辺（#55）。

### 中（設計 / インフラ）

20. 再帰の深い実装を非再帰化（§4）。
21. `#define` 依存（`op`/`merge`/`apply`/`id`/`e`/`get`/`P`/`T`）の撤廃と namespace 隔離（§6）。
22. `scripts/expander.py` の循環対策と重複排除（§8）。
23. ルート `.gitignore` 追加と `.pyc` の untrack（§8）。
24. `format.sh` の堅牢化 + CI への format チェック追加（§8）。
25. verify 未カバー 20 件の解消（§9）。
26. `io.cpp` / `dump.cpp` / `LIS.cpp` の削除、または正式に documentation・テスト対象へ追加（§5）。
27. ドキュメント未整備分（§7）の是正。

## 12. 追加が望ましいライブラリ（機能拡充候補）

現行 Geometry は「2D の基本 + 内包判定 + 凸包 + 最小包含円 + 直線/最遠点対」程度で、ICPC の定番でも欠けているものが多い。優先度順に列挙する。**◎ = #161 で追加済み**（verify 整備状況も併記）。

### 優先度 高

| 機能 | 理由 | 状態 |
|---|---|---|
| 半平面交差 (half-plane intersection) | 凸多角形の共通部分・実行可能領域。凸幾何の最頻出 | ◎ `halfPlaneInter` 追加済み（verify 未整備） |
| 点が凸多角形の内部か O(log n) | `isinPolygon` は O(n)。クエリ多数で必須 | ◎ `isinConvexPolygon` 追加済み（verify 未整備） |
| 凸多角形の共通部分（面積） | 半平面交差 or 回転カリパス | 未追加（`halfPlaneInter` で実装可能） |
| 線分と円の交点 | 現行 `clInter` は直線のみ。線分にクランプした版があると便利 | 未追加 |
| 円の合併面積 | 内包ソート + 扇型。典型問題 | 未追加 |
| 厳密整数幾何 (`IPoint` + 厳密述語) | #133 と共通基盤。スケール・環境非依存 | 未追加（#133 待ち） |

### 優先度 中

| 機能 | 理由 | 状態 |
|---|---|---|
| Minkowski 和（差分） | 凸多角形の距離・衝突判定 | 未追加 |
| 多角形の重心 (centroid) | 面積重み付き重心 | 未追加 |
| 最小外接長方形 / 最小面積長方形 | `diamConvex` の一般化（回転カリパス） | 未追加 |
| 直線と多角形の交差判定 | ビーム判定 | 未追加 |
| 3D 幾何一式（`Plane` / 点・直線-平面 / 直線間距離 / `Sphere` / 3D 凸包） | `Point3D` は点演算のみ | 未追加 |
| 偏角ソート (`argCmp` / `argSort`) | 頻出。LC に verify あり | ◎ 追加済み（yosupo `sort_points_by_argument` 21/21） |
| Manhattan ⇄ Chebyshev 変換 | 45°回転。マンハッタン距離問題の定番 | ◎ `manhattanMST` 内部で利用（yosupo `manhattanmst` 16/16） |

補足（#161 の verify）: `sort_points_by_argument` 21/21、`all_furthest_neighbors` 15/15、`manhattanmst` 16/16、AOJ `CGL_2_A` 32/32 は通過済み。verify が未整備の `halfPlaneInter` / `isinConvexPolygon` は、それぞれブルートフォース（`polygonCut` による逐次クリップ）および既存 `isinPolygon` との突き合わせでローカル検証済み（0 bad）。

その他 LC 候補と対応状況:
- `convex_layers`（O(n log n) は高度）、`count_points_in_triangle`（bitset 前計算で実装可）、`euclidean_mst`（Delaunay or グリッド）は未対応。

### 優先度 低 / 任意

- Delaunay 三角形分割 / Voronoi 図。
- 一般（非凸）多角形の共通部分（面積）。
- Pick の定理 / 格子点。
- 多角形の三角形分割。
- 線分アレンジメント / 平面走査（AOJ CGL_6_A: Manhattan 線分の交差数え上げ）。

---

## 付録: 検証方法

- Math / Graph / Structure / Geometry・Strings / インフラの 5 分野を並列レビュー。
- 主要な主張について `g++ 15.2.0 (MinGW-w64)` で実コンパイル・実実行して再現確認（`-D_GLIBCXX_DEBUG` / `-D_GLIBCXX_ASSERTIONS` を含む）。
- アルゴリズムはランダム総当たり照合（各所で数千〜20万ケース）で検証。
- `python scripts/source_urls.py check` を実行し CI の失敗を確認。
- `git ls-files` / `git ls-files -s` で追跡一覧・実行ビットを確認。
- 再帰の深さは大きなパス / 閉路入力でスタック枯渇を実測。
- 本版の状態列は、main `eec8998` の作業ツリーに対して各項目を再検証して付与（検証スクリプトは `Geometry` 追加作業時のローカル環境を再利用）。fps 関連は main `53bc47c` で再検証（yosupo verify 8 問全ケース通過＋ランダム総当たり）。
