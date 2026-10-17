# Tsukuyom1_Library 問題点一覧（検証済み版）

調査対象: `C:\Users\oxojo\Tsukuyom1_Library` (ICPC-Tsukuyom1_Library)

- 調査方法: 全 `.cpp` / `.typ` / ワークフロー / スクリプトの静的レビューに加え、`g++ 15.2.0 (MinGW-w64)` による**実コンパイル・実実行・総当たり照合**で検証。
- 凡例: **✅ = コンパイルまたは実行で再現確認した** / **⚠ = コード読解に基づく（未テストまたは条件付き）**
- 前版に含まれていた誤検出（false positive）は [§10](#10-前版からの撤回誤検出だった項目) にまとめて撤回した。

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

---

## 1. コンパイルできない / 単体でコンパイル不能なファイル

| # | 位置 | 問題 |
|---|---|---|
| 1 | ✅ `Graph/Bellman-Ford.cpp:18,24` | 関数が18行目で閉じ、19–23行目が名前空間スコープに露出（`for`/`return`）。余分な `}` が24行目。**一度もコンパイルされたことがない。** |
| 2 | ✅ `Graph/Bellman-Ford.cpp:6,10,15,20` | `INF` を使用するが、このファイルにも `template.cpp` にも定義が無い（グローバル `INF` は `mincostflow.cpp:4` のみ）。include 順依存。 |
| 3 | ✅ `Graph/Bellman-Ford.cpp:14-17` | 8–13行目と同じ緩和パスが重複し、`V+1` 回実行してしまう。 |
| 4 | ✅ `Geometry/circleTangents.cpp:7` | `i.rotate(theta, c.c)` は2引数。2次元 `Point::rotate`（`Point.cpp:25`）は1引数のみ。 |
| 5 | ✅ `Geometry/Polygon_cut.cpp:9` | `lineInter(...)[1]`。戻り値は `std::pair<bool,Point>` で `operator[]` が無い（正しくは `.second`）。 |
| 6 | ✅ `Structure/kd-tree.cpp:50-51` | `l->get(...)` / `r->get(...)`。メンバは `foreach`（`:41`）で `get` は存在しない。 |
| 7 | ✅ `Geometry/ccInter.cpp:6` | `inf` は `clInter.cpp:3` でしか定義されず、単体では未宣言。 |
| 8 | ✅ `Graph/twosat.cpp:18` | `SCC` を使用するが include / コメントが無く単体で未宣言。 |
| 9 | ✅ `Graph/directed-mst.cpp:14-15` | 依存 `SkewHeap` / `UFRollback` がコメントのみで未 include。 |
| 10 | ✅ `Math/binomial-coefficients.cpp:2` | 裸の `mint`。ライブラリ全体にグローバル `mint` 定義が無い（`matrix.cpp:3`、`solveLinear.cpp:3,37` も同様）。 |
| 11 | ✅ `Geometry/Point3D.cpp:2` × `Point.cpp` | 両方が `struct Point` を定義。同時 include で再定義エラー。 |
| 12 | ✅ `Graph/{Bellman-Ford:2, Kruskal:4, directed-mst:4}` + `rerooting.cpp:3` | 4系統の `struct Edge` が衝突。 |
| 13 | ✅ `Graph/rerooting.cpp:10,12-13,19,21-26,32-41` | `V` / `E` / `ee` / `op` / `put_edge` / `put_vert` を未定義のまま使用。`rerooting.typ` のマクロ前提が正だが、**コンパイル不能なファイルとして `.cpp` 公開されている**。 |

## 2. メモリ安全性 / 未定義動作

| # | 位置 | 問題 |
|---|---|---|
| 14 | ✅ `Strings/SuffixArray.cpp:6,12` | `vl x(all(s))` が符号付き `char` をそのまま昇格。`>=0x80` のバイトで `ws[x[i]]++` が負添字 → クラッシュ（`_GLIBCXX_DEBUG` で確認）。 |
| 15 | ✅ `Structure/BIT.cpp:7,11` | コンストラクタで `N=N_+1` の後 `rep(i,N) data[i+1]=v[i]` → `v[sz(v)]` を読む（`BIT(vector)` でアボート）。 |
| 16 | ✅ `Structure/dualsegtree.cpp:35-39` | `get(i)` に `i<n` のチェックが無く `i==n` で `2n` 添字。 |
| 17 | ✅ `Structure/wavelet-matrix.cpp:33` | `bit_width(values.size() - !values.empty())` が空入力で `size_t` アンダーフロー → `lg=64` → `1LL<<64` は UB。 |
| 18 | ✅ `Structure/LiChaoTree.cpp:12-13` | `ll n;` が既定コンストラクタ `LCTree() {}` で未初期化。 |
| 19 | ✅ `Structure/LiChaoTree.cpp:18` | `while (sz(x)<n) x.push_back(x.back())` が空 `x` で `back()` = UB。 |
| 20 | ✅ `Structure/LiChaoTree.cpp:56-58` | `query(t)` が `t > max(x)` で `seg[2n]` を参照（定義域チェック無し、未記載）。 |
| 21 | ✅ `Structure/SparseTable.cpp:17` | `fold(l,l)` で `__lg(0)` = UB、かつ負添字読み。 |
| 22 | ✅ `Structure/disjoint-sparsetable.cpp:23` | `fold(l,l)` で `__lg(l ^ r)` = `__lg(-1)`、クラッシュ。 |
| 23 | ✅ `Structure/binary-trie.cpp:87-98` | `at(k)` に境界チェックが無く `k>=size()` で null 参照。 |
| 24 | ✅ `Math/fps.cpp:249-254` | `shift()` が空多項式で `rfact[n-1]`（`rfact[-1]`）を参照。 |
| 25 | ✅ `Math/fps.cpp:220-225` | `pow(0,0)` で `P res(0)` に `res[0]=1`。 |
| 26 | ✅ `Math/fps.cpp:197` | `sqrt()` が空で `(*this)[0]` を参照。 |
| 27 | ✅ `Math/BigInt.cpp:167-177` | `divmod()` に除数ゼロのガードが無く、`BigInt/0` でゼロ除算クラッシュ。 |
| 28 | ✅ `Math/binomial-coefficients.cpp:4-21,25` | `init(n)` が `pascal` を消去しない。`init(10)` → `init(5000)` の後 `com(4000,2)` で範囲外。 |
| 29 | ✅ `Math/golden_section_search.cpp:3,6` | 固定 `eps=1e-7`。最小値が巨大座標（例: `f=(x-1e18)^2`）だと `r-l` が縮まず**無限ループ**。 |
| 30 | ✅ `Geometry/area.cpp:4` | 空多角形でも `S[0]` を無条件参照。 |
| 31 | ✅ `Geometry/minEncloseCirc.cpp:5,13` | 空入力で `ps[0]` / 重複点で外心計算が縮退し NaN。 |
| 32 | ✅ `Geometry/diamConvex.cpp:6` | 空入力で `Q[0]` を参照。 |
| 33 | ✅ `Structure/swag.cpp:16-17` | `front()` / `back()` に空チェックが無い。 |
| 34 | ✅ `Structure/hld.cpp:15` | `g[v].erase(find(all(g[v]), par[v]))`。8行目の契約（親→子のみ）だと `find` が `end()` を返し `erase(end())` = UB。 |
| 35 | ✅ `Math/matrix.cpp:30` | `operator*=` が次元チェック無し。`A(2,3)*=B(2,2)` で範囲外アクセス。 |
| 36 | ⚠ `Math/modint.cpp:43` | `ll x * p.x % mod()` は `MOD > ~3e9` でオーバーフロー（`__int128` 未使用。`modula.cpp:2` は使用しており不整合）。 |
| 37 | ⚠ `Math/modula.cpp:10-18` | `modlog` の `e*a%p` 等が素の `ll`。`p` が約 3e9 超でオーバーフロー。 |
| 38 | ⚠ `Math/extgcd.cpp:6` | `Y -= (A/B)*X` が大きい `|A|,|B|` で `ll` オーバーフロー。負入力では `%` の不変条件が崩れる。 |
| 39 | ⚠ `Math/floorsum.cpp:7,12` | `n*(n-1)/2*(a/c)` / `a*(n-1)+b` が `ll` オーバーフロー。 |
| 40 | ⚠ `Structure/BIT.cpp:32,43` | `1 << (__lg(N)+1)` のリテラル `1`。`N>=2^30` で負シフト / UB。 |
| 41 | ⚠ `Structure/LiChaoTree.cpp:5,41` | 「無限大」に `LLONG_MAX/4`、`1 << ub` も `int` シフト。`2.3e18` 以上の値は有限扱い。 |
| 42 | ⚠ `Math/fps.cpp:151-158` | `operator()(T x)` が `mod` で還元せず素の整数を返す → オーバーフロー、体の値と不一致。 |
| 43 | ⚠ `Geometry/clInter.cpp:3` / `ccInter.cpp:6` | 「無限遠点」`-inf` は `LDBL_MAX/2` の**有限値**。算術と組み合わせるとゴミになる。 |

## 3. 正当性のバグ（ロジック）

| # | 位置 | 問題 |
|---|---|---|
| 44 | ✅ `Graph/flow.cpp:56` | `max_flow(s,s)` が無限ループ（`find(s,s,INF)` が毎回 `INF` を返す）。 |
| 45 | ✅ `Structure/segtree.cpp:34-46` | `max_right(f)` が `[0,N)` ではなくパディング後の `[0,next_pow2(N)]` の添字を返す（`N` を保持していない）。 |
| 46 | ✅ `Structure/hld.cpp:32-44` | `queryPath` は非可換モノイドで `u→v` の順にならない（`queryPath(u,v)==queryPath(v,u)`）。 |
| 47 | ✅ `Math/matrix.cpp:27-33` | `operator*=` が結果配列を差し替えるがメンバ `m` を更新しない → 以降の次元が崩れる。 |
| 48 | ✅ `Math/fps.cpp:7-8,48-55,89-103,174-177` | `set_mod()` が実質無効。継承した `vector<T>` のコンストラクタが `mod` / `root` を既定 `998244353` / `3` に戻す。 |
| 49 | ✅ `Math/bitwise_xor_convolution.cpp:18` | `T iv = T(1)/sz(a);` が `T=ll` で整数除算（`>1` で0）→ 全ゼロ。 |
| 50 | ✅ `Math/binomial-coefficients.cpp:19` | `inv[i]=inv[i-1]/i` が1要素につき1回逆元計算 → `O(n log p)`。`n>=p` で静かに誤答。 |
| 51 | ⚠ `Math/binomial_coefficients.cpp:14` | `finv[n]=fac[n].inv()` が `n<mod` 前提。`n>=mod` で `inv()` の assert / 0 除算。 |
| 52 | ⚠ `Math/LucasBinom.cpp:5,10-13` | 既定引数 `Mint::mod()-1` が `mod` 長の配列を確保（`998244353` で GB 級、実用不可）。`modint<0>` 未設定時は `%0`。 |
| 53 | ⚠ `Math/modula.cpp:10-18,42` | `modlog` は `gcd(a,p)=1` 前提、`modinv` は素数前提。前提が未記載で合成数で静かに誤答。 |
| 54 | ⚠ `Math/FastFactorize.cpp:4-18` | `pollard` の失敗処理が無く `n` を返すと無限再帰の恐れ。`fac(0)` は `modmul(x,x,0)` で `%0`。`Euler_phi(0)` も同様。 |
| 55 | ⚠ `Graph/SCC.cpp:42-49` | 縮約 `dag` に重複辺の除去が無い（多重辺がそのまま）。下流の DP が誤る。 |
| 56 | ✅ `Geometry/isconvex.cpp:6-7` | 空・3点未満の多角形で `true`。自己交差の星形も `true`。 |
| 57 | ✅ `Geometry/clInter.cpp:5-14` | `dd` が符号付きなのに `sign(dd-c.r)` で符号を無視。中心が負側で `sqrtl(負)` = NaN。 |
| 58 | ✅ `Geometry/ccInter.cpp:11` | 同心円 / 零半径で `d=0` のゼロ除算、`acosl` 未クランプで NaN。 |
| 59 | ✅ `Geometry/commonTangents.cpp:9,26,10-11,17,29` | ガード `Δr<=d+EPS` 等が効かず `sqrtl(負)` = NaN。接点で `h==0` → ゼロ長の「線」。 |
| 60 | ✅ `Geometry/lineInter.cpp:5` | 平行 / 共線で `{1,(0,0)}` という偽の交点（原点が実頂点として混入し得る）。 |
| 61 | ✅ `Geometry/circumcircle.cpp:5-6` | `b.cross(c)` が共線 / 重複点で 0 → 除算で inf / NaN。 |
| 62 | ✅ `Strings/KMP.cpp:12-14` | 空パターンで偽の解の列を返す（正解は `|s|+1`）。 |
| 63 | ⚠ `Math/solveLinear.cpp:50` | `while (a[i][j].x==0) j++;` に `j<m` の上限が無い。 |
| 64 | ⚠ `Math/fps.cpp:165-170,188-193` | `integral` / `log` が次数 `mod` 到達や空系列で `modinv(0)` / 負オフセット。 |
| 65 | ⚠ `Structure/weightedunionfind.cpp:7,22` | `find` / `size` が `int`、`n` は `ll`。`n>2^31` で切り詰め。 |
| 66 | ⚠ `Structure/binary-trie.cpp:62,70` | `erase` が葉の `cnt=0` にして**重複を全消去**（`insert` / `count` は重複を数える）。 |
| 67 | ⚠ `Structure/RollingHash.cpp:14` | `S[i]` が符号付き `char`。`>=128` で不一致。`base=150` 固定で非乱数。 |
| 68 | ⚠ `Graph/Kruskal.cpp:12-13` | 同コスト辺の順序が非決定的（`std::sort` は不安定）。MST コストは不変だが返る辺集合は実行ごとに変わる。 |
| 69 | ⚠ `Graph/topological.cpp:13-22` | 閉路の検出が無く、部分順序を返してエラー信号も無い。 |
| 70 | ⚠ `Graph/twosat.cpp:22` | 充足不能が `{}` で表現され `N==0` と区別できない。 |

> 注: `Math/matrix.cpp:54-75` の `det()` は `Matrix<ll>` では整数除算で誤る（体を仮定）。`Math/modint` の `inv()` / `Math/modula` の `modinv` は素数 MOD 前提。

## 4. スタックオーバーフロー（再帰）

CI が `ulimit -s unlimited` を付けるため露見しにくいが、実ジャッジ / `run.sh` では落ちる。✅ 実測で `0xC00000FD` を確認:

- `Graph/flow.cpp:36-50`（Dinic `find`、パス 10^6 ノードで落ちる）
- `Graph/SCC.cpp:15-26`
- `Graph/LowLink.cpp:16-36`
- `Graph/lca.cpp:10-16`（パス約 5万〜10万で落ちる）
- `Graph/Centroid-Decomposition.cpp:20-34`（生の木の深さに比例）
- `Graph/rerooting.cpp:14,31`（約 5万で落ちる）
- ⚠ `Structure/hld.cpp:17,27`、`Structure/skew-heap.cpp:17-23`（深さ制限なし `merge`）
- ⚠ `Graph/maxMatching.cpp:9-24`、`Graph/hopcroftKarp.cpp:9`（理論上のみ、実測では非再現）

## 5. パフォーマンス / デッドコード / リーク

- `Structure/kd-tree.cpp:31-32` — `new` でデストラクタ無し → **全面リーク**。`function<T(T,T)> op` をノード毎に保持。
- `Structure/binary-trie.cpp:31,67` — `new` でリーク。
- `Structure/skew-heap.cpp:25` — `pop` がノードを捨てる（リーク）。
- `Graph/directed-mst.cpp:17,28,34` — `new H` が O(E) リーク。
- `Structure/dynamic-{segtree,dualsegtree,lazysegtree}.cpp:4` — グローバル `alloc` が解放不能。常に両子を確保し、読み取りクエリでも木全体が実体化。
- `Math/fps.cpp:33` — NTT 長が 2 のべき乗で必要量の 2 倍（`bit_ceil` であるべき）。
- `Math/fps.cpp:168,214,254`（および `binomial` 系）— 係数ごとに逆元計算で `O(n log mod)`。
- ⚠ `Math/fps.cpp:105-115` — `%=` / `div_mod()` が `*this` を破壊（前版の主張、今回は未再確認）。
- `Graph/LowLink.cpp:5,9` / `Graph/maxMatching.cpp:4,72` — 引数＋メンバで隣接リストを二重コピー。
- ⚠ `Math/primroot.cpp:4-8` — `rnd` 呼び出し毎に `random_device` を生成。
- ⚠ `Structure/LiChaoTree.cpp:14-15` — `const vector<ll>&` をメンバにコピーしてソート、座標の重複除去なし（`n` が最大 2 倍）。
- ⚠ `Structure/SparseTable.cpp:5` / `disjoint-sparsetable.cpp:5` — トリム無しの `n×log n`。
- `Graph/flow.cpp:6,14` — `isrev` / `idx` が未読。/ `Graph/LowLink.cpp:4` `n` 未使用。/ `Graph/directed-mst.cpp:21` `comp` 未使用で即シャドー。/ `Graph/Centroid-Decomposition.cpp:41` 常に真。/ `Structure/dynamic-lazysegtree.cpp:19` ローカル `m` がメンバを隠蔽（スコープ内で無害）。
- `Math/fps.cpp:229` `T rev` がメンバ `rev()` を隠蔽 / `:140,146` `sz` がマクロを隠蔽 / `Math/matrix.cpp:67` `T vv` が型 `vv` を隠蔽（偶然動作）。
- ルート `io.cpp`(181行) / `dump.cpp`(8行) / `LIS.cpp`(14行) は**完全な孤児**（include / `.typ` / verify すべてゼロ）。`io.cpp:2-9` は `template.cpp:21-28` の `chmax`/`chmin` を二重定義。`io.cpp:175-181` は既定で `fixed`+`setprecision(16)` に変更（`chapter.typ` は 12 と記載）。

## 6. ファイル結合時の衝突（根本設計問題）

各 `.cpp` は include 展開で 1 つの翻訳単位に連結される前提だが、名前空間スコープが衝突している。

- ✅ `Structure/swag.cpp:3` — `#define get(v) ...` がグローバル漏洩。`kd-tree` / `LiChaoTree` / `std::get` を破壊する。**ディレクトリ内で最も危険な 1 行。**
- ✅ `Structure/dynamic-{segtree,dualsegtree,lazysegtree}.cpp:4` — グローバル `alloc` が 3 系統、2 つ同時 include でコンパイル不能。
- マクロ `T/e/op`（segtree, SparseTable, disjoint-sparsetable）、`F/id/merge/apply`（lazy / dual）、`szt`（bitwise_*）が全空間に漏れ、相互排他。**この契約が `.typ` に皆無**。
- `Structure/pbds.cpp:4` — `using namespace __gnu_pbds;` が `tree` / `less` / `priority_queue` / `hash_map` を注入。
- `Graph/hopcroftKarp.cpp:3` — ライブラリ唯一の自由関数 `dfs`。
- `Math/primroot.cpp:4` — グローバル `ll rnd(ll,ll)`。
- `Math/binomial-coefficients.cpp:2` vs `FastFactorize.cpp:14` — `vec<mint> fac` と `vl fac(ll)` が衝突（✅ 再現: `'fac' redeclared as different kind of entity`）。
- `Math/binomial-coefficients.cpp:4` `void init(ll)` vs `io.cpp:175-181` `struct init`。
- `Geometry/Point.cpp:7` `typedef Point P` vs `closest_pair.cpp:3` `#define P Point`。
- `Math/matrix.cpp:3` / `solveLinear.cpp:3` が裸の `mint` を要求（ユーザ定義が必要）。
- `Graph/mincostflow.cpp:4` の唯一のグローバル `const ll INF`（配置が他と不整合）。`Graph/mincostflow.cpp:2` は `<bits/extc++.h>` を include（GCC 内部ヘッダ、非移植）。

## 7. ドキュメントの欠陥

- ✅ `Structure/segtree.cpp:6` コメント「構築 O(N log N)」は誤り（実際 `O(N)`）。
- `Math/binomial_coefficients.typ:5` — `read("binomial-coefficients.cpp")` で**死んだ側の実装**を読む。現行 `binomial_coefficients.cpp` は `.typ` 無し・URL ヘッダ無し。
- `Structure/weightedunionfind.typ:18,26` — 存在しない `connected` / `diff` を記載（実体は `find` / `merge` / `size` / `weight`）。`:5` にプレースホルダ `*なにこれ*`。
- `Math/extgcd.typ:5` — 「`a x+b y=c` を解く」は嘘（返り値は gcd）。
- `Geometry/projection.typ:5` — `reflect` の説明が実装と**逆**。
- `Geometry/LineDistance.cpp:5` — **符号付き**距離である旨が未記載。
- `Geometry/lineInter.typ:4` / `ccInter.typ:3-4` — 平行・非交差の返り値の説明が実装と不一致 / `-inf` は有限値。
- `Graph/hopcroftKarp.typ` — 返り値が**2倍**であること（呼び出し側の `/2` 必須）が未記載。右側の `btoa` が非対称になり得る点も未記載。
- `Graph/kruskal.typ:5` — `O(E log V)` は誤り（`O(E log E)`）。非連結時に全域**森**になる旨も未記載。
- `Graph/PushRelabel.typ` — 使用法（`rcap`、再入不可）が皆無。
- `Graph/bellman-ford.typ` — **コンパイルできないソース**をそのまま提示。
- `Graph/{lca,LowLink,topological,twosat,Centroid-Decomposition}.typ` — 見出し＋1行のみ。`twosat.typ` に誤字。
- `Graph/rerooting.typ` — `mint` 前提を書くが modint 依存が不明。
- `Structure/dynamic-*.typ` など — `T/e/op/F/id/merge/apply` を事前 `#define` する契約が未記載。
- `Structure/pbds.typ:14` — `ull` を使うが `template.cpp` に `ull` が無くコンパイル不可。
- `chapter.typ:26` — `Math/modint.typ` を「Template」章に直接入れ、`Math/chapter.typ` は modint を含まない（レイヤリング違反）。
- `Math/{matrix,fps,modint,binomial_coefficients}.typ` — ソースのみで散文ゼロ。`Math/LucasBinom.cpp` は `.typ` 無し。
- `Documents/Trigonometry.typ:6,9` — 加法定理が誤り（`cos x`、余弦の符号誤り）。`Documents/math.typ:48,56,58,64` — 係数・級数の誤り。`Documents/combination.typ:7,84,136` — 誤り / 誤字。`Documents/parallel-binsearch.typ:8` — 計算量が誤り。
- `README.md:3` — プレースホルダ「追加して～」。`:20` の `expander.py` の使い方は引数1つ必須を無視。verify の yukicoder トークン要件、カバレッジ系スクリプトが未記載。

## 8. CI / スクリプト / リポジトリ衛生

- ✅ `python scripts/source_urls.py check` が終了コード 1（`Math/LucasBinom.cpp:1`、`Math/binomial_coefficients.cpp:1`、`Math/modint.cpp:1` に URL ヘッダ欠落）→ `source-urls.yml` は赤。
- ✅ ルートに `.gitignore` が無く、`scripts/__pycache__/source_urls.cpython-312.pyc` が追跡下。
- ✅ `run.sh` は 100644・shebang なし・`-static`・`_GLIBCXX_DEBUG`。`./dist` / `./input` が未作成でそのままは動かない。`:1` のコメント「`.cpp` へ変換」は嘘。
- ✅ `format.sh:3-4` は `dirname $0` 未クォート、`find . -name "*.cpp" | xargs` で無濾過（`verify` やビルド出力も対象）、CI から未呼び出し。
- `.github/workflows/verify.yml:130,134` — yukicoder は `secrets.YUKICODER_TOKEN` 必須。fork PR で全滅。
- `verify.yml:254-259` — カバレッジ artifact が 1 つも無いと `download-artifact` がエラー終了。
- `verify.yml:65` — `DIR` を代入前に `echo`。`:69` は Python セットアップ無しで generate。`:103` grep に重複排除 / ソート無し。`matrix.problem` を無害化せず shell へ埋め込み（インジェクション余地）。
- `scripts/expander.py:16` — 循環 include 対策（訪問済み集合）が無く `RecursionError`、重複排除も無い。テスト無し・CI 未呼び出し。`:19` の `f"\n"`（不要な f プレフィックス）。
- `scripts/aggregate_coverage.py:37-41` — `git ls-files` ではなく `root.rglob("*.cpp")` で未追跡ファイルまで拾う。
- `.devcontainer/Dockerfile:2-3` — `g++` / `python3` / `typst` 等が無く、コンテナ内で `run.sh` / `format.sh` / docs / verify が一切動かない。`clang-format` はバージョン未固定。
- `.vscode/settings.json` — `files.eol: "\n"` が無く、`core.autocrlf=true` 環境で `*.sh` が CRLF 化して Linux で壊れる。
- 実行ビットが場当たり（`docs/build.sh` / `format.sh` / `expander.py` は 755、`run.sh` / `source_urls.py` は 644）。

## 9. 命名の不統一 / テストカバレッジ

- `.cpp` ↔ `.typ` のベース名不一致が多数: `isinpolygon`↔`isinPolygon`、`LineDistance`↔`lineDistance`、`Bellman-Ford`↔`bellman-ford`、`Kruskal`↔`kruskal`、`SCC`↔`scc`、`Euler_phi`↔`euler_phi`、`BIT`↔`bit`、`BIT2d`↔`bit2d`、`RollingHash`↔`rollinghash`、`SparseTable`↔`sparsetable`、`UnionFind-rollback`↔`unionfind-rollback`、`binomial_coefficients.typ`↔`binomial-coefficients.cpp`。
- 関数名の不一致 / タイポ: `circleTangents.cpp`→`circTangents`、`trincircle.cpp`→`trinCircle`、`ZAlgorithm.cpp`→`Zalgo`、`Structure/LiChaoTree.cpp`→`LCTree`。
- セグメント木系の命名が 6 通り（`SegTree` / `LazySeg` / `DualSeg` / `DynamicSeg` / `DynamicLazySeg` / `DynamicDualSeg`）。
- **verify に include されていないライブラリ `.cpp` が 27 件**: `Graph/{Bellman-Ford,flow,PushRelabel,Centroid-Decomposition,LowLink,topological}`、`Geometry/{circleTangents,clInter,ccInter,commonTangents,isconvex,Polygon_cut,Point3D,LineDistance,CircCircInter,CircPolyInter,trincircle}`、`Strings/KMP`、`Math/{extgcd,garner,Euler_phi,binomial-coefficients}`、`Structure/{BIT2d,RollingHash}`、`io.cpp` / `dump.cpp` / `LIS.cpp`。§1〜§3 のバグが生き延びた原因。

## 10. 前版からの撤回（誤検出だった項目）

前版 `LIBRARY_ISSUES.md` の一部は過大な断定でした。今回の検証で**バグではない**と確認したもの:

- **PushRelabel の最大流が壊れている（前版 #21）** — 誤り。`H[u]=1e9` 番兵は必ず上書きされ範囲外にならない。Edmonds–Karp / Dinic と 20 万ケース以上一致（`_GLIBCXX_DEBUG` でも OOB 無し）。
- **mincostflow のダングリングポインタ（前版 #83,#86）** — 通常使用では再確保されず問題なし。
- **`maxMatching.cpp` の `gr[-1]`（前版 #20）** — 到達不能。20 万ケースで非再現。
- **`kd-tree.cpp:10` の `sum=e`（前版 #17）** — メンバ初期化順序的に問題なし（`e` は先に初期化済み）。
- **`lazysegtree.cpp` の即時 flush で `O(区間)` 劣化（前版 #47,#48）** — 依然 `O(log n)` で結果も正しい（300 ケース検証）。ただし `:27` が無関係ノードまで push するのは無駄。
- **`diamConvex.cpp` の剰余欠落（前版 #9）** — `%n` は存在し、アルゴリズムは 3000 多角形で総当たりと一致（空入力の `:6` のみ UB）。
- **`closest_pair.cpp:11` の erase（前版 #73）**、**`segInter.cpp` の set / onSegment 不整合（前版 #77）**、**`ccInter` が `commonTangents` を呼ぶ点（前版 #71 は性能問題のみ）**、**`CircPolyInter` の `arg` が `std::arg` を隠蔽（前版 #127）**、**`CircCircInter`/`CircPolyInter` の `fac` 衝突（前版 #126）** — いずれも実際にはバグではありません（オーバーロード / no-op）。
- **`SuffixArray.cpp` の `y[a+j]` 範囲外（前版 #18）** — 短絡評価により実測では再現せず。
- **`flow.cpp` の自己ループで `rev` が壊れる（前版 #82）** — Dinic は自己ループを走査しないため結果に影響なし（潜在的な脆さのみ）。

## 11. 優先度付き修正リスト

### 最優先（CI 復旧 + コンパイル不能 + メモリ安全）

1. `Math/{modint,binomial_coefficients,LucasBinom}.cpp:1` に URL ヘッダを追加（CI 復旧）。
2. `Graph/Bellman-Ford.cpp` の波括弧・`INF`・`return` を修正。
3. `Structure/kd-tree.cpp:50-51` の `get` → `foreach`。
4. `Geometry/Polygon_cut.cpp:9` を `.second` に。
5. `Geometry/circleTangents.cpp:7` の `rotate` 引数整合。
6. `Geometry/Point3D` / `Edge`（4系統）/ `alloc`（3系統）/ `fac` の名前衝突解消。
7. `Strings/SuffixArray.cpp:6` に `static_cast<unsigned char>`。
8. `Structure/BIT.cpp:11` の `rep(i, N)` を修正、`dualsegtree.cpp:35` / `wavelet-matrix.cpp:33` / `LiChaoTree` / `SparseTable` / `disjoint-sparsetable` の境界・空ガード。
9. `Math/BigInt.cpp:167` の除数ゼロガード、`Math/fps.cpp` の空入力ガード。

### 高（正当性）

10. `Graph/flow.cpp:56` の `max_flow(s,s)`。
11. `Math/matrix.cpp:27` の `m` 更新漏れ、`:76` の `inv()` をローカルコピーに。
12. `Math/fps.cpp:7` の `set_mod` 無効を修正、`:33` の `bit_ceil`。
13. `Math/bitwise_xor_convolution.cpp:18` の整数除算。
14. `Geometry/{isconvex,clInter,commonTangents,ccInter,circumcircle,lineInter}` の数値・論理。
15. `Strings/KMP.cpp` の空パターン。
16. `Structure/segtree.cpp` の `max_right` 添字クランプ。

### 中（設計 / インフラ）

17. 再帰の深い実装（`lca` / `SCC` / `LowLink` / `Centroid-Decomposition` / `flow` / `rerooting` / `hld` / `skew-heap`）を非再帰化。
18. `#define` 依存（`op` / `merge` / `apply` / `id` / `e` / `get` / `P` / `T`）をやめ、ファイル毎に `namespace` 隔離。
19. `scripts/expander.py` に訪問済み集合と include ガード対応を実装。
20. ルート `.gitignore` を追加し `.pyc` を `git rm --cached`。
21. `format.sh` を `git ls-files` ベースにし、クォートを付与。CI に format チェックを追加。
22. verify を全ライブラリファイルに対して網羅的に用意。
23. `io.cpp` / `dump.cpp` / `LIS.cpp` を削除、または正式に documentation・テスト対象へ追加。

---

## 付録: 検証方法

- Math / Graph / Structure / Geometry・Strings / インフラの 5 分野を並列レビュー。
- 主要な主張について `g++ 15.2.0 (MinGW-w64)` で実コンパイル・実実行して再現確認（`-D_GLIBCXX_DEBUG` / `-D_GLIBCXX_ASSERTIONS` を含む）。
- アルゴリズムはランダム総当たり照合（各所で数千〜20万ケース）で検証。
- `python scripts/source_urls.py check` を実行し CI の失敗を確認。
- `git ls-files` / `git ls-files -s` で追跡一覧・実行ビットを確認。
- 再帰の深さは大きなパス / 閉路入力でスタック枯渇を実測。
