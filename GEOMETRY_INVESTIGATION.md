# Geometry 調査レポート

- 対象 issue: **#133「Geometry 微調整」（極力 eps を使わずに行きたい）** / **#144「geometry」（追加機能）**
- 目的: 「出力結果以外の過程（分岐・判定）が浮動小数誤差に左右されない」ようにするための調査と、ICPC ライブラリとして追加すべき幾何機能の洗い出し。
- 調査ブランチ: `research/geometry-exactness`

---

## 0. 用語

| 用語 | 意味 |
|---|---|
| **過程 (predicate)** | 分岐・判定。「交差するか」「凸か」「点は多角形の内側か」「接するか」など、アルゴリズムの流れを決める真偽値・符号。 |
| **出力 (value)** | 交点座標・距離・面積など、最後に印字する数値。 |

#133 の精神は「**過程を厳密に、出力だけ浮動小数**」に寄せること。

---

## 1. 現状の eps 依存の棚卸し

`Geometry/Point.cpp` が根で、以下を定義している。

```cpp
#define EPS (1e-10)
#define eq(a, b) (fabs((a) - (b)) < EPS)
ll sign(ld x) { return (x >= EPS) - (x <= -EPS); }
```

この `EPS` / `eq` / `sign` が全ファイルに波及している。用途ごとに分類すると:

| ファイル | eps/誤差に依存する箇所 | 種別 | 厳密化 |
|---|---|---|---|
| `Point.cpp` | `EPS`, `eq`, `sign`, `operator==` | 根 | 整数型を併設して根から除去 |
| `ccw.cpp` | `cross` と `dot` を `±EPS` と比較 | **過程** | ◎ 整数 `__int128` で厳密 |
| `onSegment.cpp` | `eq(cross,0)` かつ `dot <= EPS` | **過程** | ◎ |
| `segInter.cpp` | `sign(oa)*sign(ob)<0 ...` + `onSegment` | **過程** | ◎ |
| `lineInter.cpp` | `sign(d)`（平行判定） | **過程** | ◎ |
| `ssDist.cpp` | `segInter` の結果で分岐 | **過程** | ◎（`segInter` 次第） |
| `segDistance.cpp` | 距離は出力、`s==e` 判定は `operator==` | 出力＋過程 | ◎ |
| `projection.cpp` | `base.abs() < EPS` 退化判定 | **過程** | ◎（`base == 0`） |
| `convex_hull.cpp` | `a.cross(b) <= ±EPS`（共線除去） | **過程** | ◎ |
| `isconvex.cpp` | `sign(cr)` と総回転角 `2π`（`atan2l`） | **過程** | △ 回転角を winding number に置換すれば厳密 |
| `diamConvex.cpp` | `cross > -EPS` | **過程** | ◎ |
| `closest_pair.cpp` | 距離比較（`ld`） | 出力 | △ 二乗距離の `__int128` 比較で厳密 |
| `minEncloseCirc.cpp` | `c.r*eps`（`1+1e-10` の相対許容） | **過程** | △ 二乗距離の厳密比較で置換可 |
| `isinpolygon.cpp` | `abs(cross)<EPS`, `A.y<EPS`, `cross>EPS` | **過程** | ◎ |
| `Polygon_cut.cpp` | `sign(s.cross(e,cur))<0` | **過程** | ◎ |
| `circumcircle.cpp` | `fabsl(d) < EPS`（共線判定） | **過程** | ◎（`cross` で厳密） |
| `trincircle.cpp` | なし（`Area` 使用） | 出力 | – |
| `area.cpp` | なし（符号付き面積） | 出力 | – |
| `LineDistance.cpp` | なし（符号付き距離） | 出力 | – |
| `clInter.cpp` | `sign(dd - c.r)`（直線と円の交差判定） | **過程** | ○ 整数なら `cross^2` vs `r^2*|base|^2` で厳密 |
| `ccInter.cpp` | `commonTangents` の本数（eps 依存）で交差判定、`acos` クランプ | **過程** | ○ 二乗距離で厳密判定 |
| `commonTangents.cpp` | `d < EPS`, `\|r1-r2\| <= d+EPS`, `r1+r2 <= d+EPS` | **過程** | ○ 二乗距離で厳密 |
| `CircCircInter.cpp` | `sign(dd-(r1+r2)^2)`, `sign((r1-r2)^2-dd)` | **過程** | ◎（半径・中心が整数なら厳密） |
| `CircPolyInter.cpp` | `sign(det)`, `sign(s)`, `sign(t-1)`, `sign(t)`, `sign(s-1)` | **過程** | ○ 一部は実数本質 |
| `circleTangents.cpp` | `acos` クランプのみ | 出力 | – |
| `Point3D.cpp` | なし | – | – |

**結論**: 分岐を持つ関数のほぼすべてが `EPS` 依存。特に「共線」「接する」「退化」を `EPS` で判定している。

---

## 2. なぜ eps が問題か（実験で確認）

### 2.1 スケール依存（絶対 eps の限界）

同じ形を縮小しただけで `ccw` の答えが変わる。

```
[ccw scale] s=1e0   -> CCW
[ccw scale] s=1e-3  -> CCW
[ccw scale] s=1e-4  -> ON_SEGMENT   ← 本物の CCW が退化扱い
...
[ccw scale] s=1e-15 -> ON_SEGMENT
```

同様に、辺の長さ `1e-6` の正三角形は `convex_hull` が 2 頂点しか返す（本来 3）。

```
[convex_hull tiny] vertices: 2 (exact would be 3)
```

`EPS = 1e-10` は**絶対値**なので、座標のスケール（単位）が変わると意味が変わる。

### 2.2 `long double` の精度限界（座標が大きいとき）

`ld` の仮数は処理系依存で、座標が大きいと `cross` の積が丸まる。厳密 `__int128` 実装と総当たり比較（`convex_hull(str=true)`）:

```
R=1e6   : 0/2000   mismatch
R=1e9   : 0/2000   mismatch
R=1e18  : 53/2000  mismatch
```

R=1e18 の失敗例（ライブラリが頂点を 1 つ落としている）:

```
in : (571428571428571428,571428571428571429) (857142857142857143,857142857142857142)
     (428571428571428570,428571428571428572) (428571428571428571,428571428571428572)
     (714285714285714286,714285714285714286)
lib : (428571428571428570,428571428571428572) (428571428571428571,428571428571428572)
      (857142857142857143,857142857142857142)
exact:(428571428571428570,428571428571428572) (428571428571428571,428571428571428572)
      (714285714285714286,714285714285714286) (857142857142857143,857142857142857142)
```

`isinPolygon` でも（R=1e18 で 2/16000 クエリ）境界上の点を内側と誤判定:

```
q=(-477351413675829127,438142854735512539)  lib=1(境界) exact=2(内側)
```

**注意（重要）**
- 整数座標が小さい（≦1e9 程度）問題では、積が `ld` の仮数（64bit）に収まり**たまたま厳密**になるため、現行 eps は実害が出にくい。実際 R=1e6, 1e9 では不一致 0 だった。つまり現行コードは「整数座標の小さめの問題だけなら動く」状態。
- 一方で **`long double` の精度は環境依存**（x86-64 Linux: 80bit / aarch64 Linux: binary128 / MSVC や macOS arm64: `double` と同じ 53bit）。移植すると同じコードが壊れる。`__int128` なら環境非依存で厳密。

つまり eps を消して厳密整数述語にすると、**スケール非依存・環境非依存・座標上限の拡大**が同時に得られる。

---

## 3. #133 の設計案

### 3.1 原則

1. **判定はすべて整数演算（`__int128`）で行う。**
2. **出力のみ `long double`（必要なら有理数）。**
3. `EPS` は「出力の丸め」以外では使わない（`eq`/`sign` を既定経路から外す）。
4. 退化（共線・重複・接する・一直線）は **eps ではなく明示的に分岐**して扱う。

### 3.2 述語の厳密化（例）

```cpp
using i128 = __int128_t;

// 整数点（eps を一切使わない比較）
struct IPoint {
  ll x, y;
  bool operator<(const IPoint& p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(const IPoint& p) const { return tie(x, y) == tie(p.x, p.y); }
  IPoint operator+(const IPoint& p) const { return {x + p.x, y + p.y}; }
  IPoint operator-(const IPoint& p) const { return {x - p.x, y - p.y}; }
  IPoint operator*(ll k) const { return {x * k, y * k}; }
};

// 符号（厳密）
inline int sgn(i128 v) { return (v > 0) - (v < 0); }

// 外積（厳密）。座標 ≦1e9 なら積 ≦1e18 で i128 に余裕。
inline i128 cross(const IPoint& o, const IPoint& a, const IPoint& b) {
  return (i128)(a.x - o.x) * (b.y - o.y) - (i128)(a.y - o.y) * (b.x - o.x);
}
inline i128 cross(const IPoint& a, const IPoint& b) {
  return (i128)a.x * b.y - (i128)a.y * b.x;
}
inline i128 dist2(const IPoint& a, const IPoint& b) {
  i128 dx = a.x - b.x, dy = a.y - b.y;
  return dx * dx + dy * dy;
}
```

これで:

```cpp
// ccw: eps 不要
int ccw(const IPoint& A, const IPoint& B, const IPoint& C) {
  i128 c = cross(A, B, C);
  if (c > 0) return COUNTER_CLOCKWISE;
  if (c < 0) return CLOCKWISE;
  // 共線は厳密なドット積で前後を決める
  i128 d = (i128)(B.x - A.x) * (C.x - A.x) + (i128)(B.y - A.y) * (C.y - A.y);
  if (d < 0) return ONLINE_BACK;
  i128 lb = (i128)(B.x - A.x) * (B.x - A.x) + (i128)(B.y - A.y) * (B.y - A.y);
  i128 lc = (i128)(C.x - A.x) * (C.x - A.x) + (i128)(C.y - A.y) * (C.y - A.y);
  return lb < lc ? ONLINE_FRONT : ON_SEGMENT;
}
```

```cpp
// 線分交差（厳密）
bool onSegment(const IPoint& a, const IPoint& b, const IPoint& p) {
  if (cross(a, b, p) != 0) return false;
  return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
         min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
```

```cpp
// convex_hull（単調鎖法、共線判定は符号で厳密に）
Polygon hull(const vec<IPoint>& p, bool drop_collinear) {
  // pop 条件: drop_collinear ? cross <= 0 : cross < 0
}
```

```cpp
// isinPolygon: レイキャストも厳密な符号比較に（EPS 不使用）
//   交差距離の比較は (q.x-p.x)*(a.y-p.y) と (a.x-p.x)*(q.y-p.y) の i128 比較で行う
```

**円まわり**（実数が本質的だが、中心・半径が整数なら厳密化できる）:

```cpp
// 直線 l と円 (c, r): 交差判定も接判定も厳密
//   |cross(e-s, c-s)| / |e-s| と r の比較  ⇔  cross^2 と r^2 * |e-s|^2 の比較
i128 dc  = cross(l.e - l.s, c.c - l.s);
i128 rhs = (i128)c.r * c.r * dist2(l.s, l.e);
// dc*dc > rhs  -> 交差しない（厳密）
// dc*dc == rhs -> 接する（厳密）
```

```cpp
// 円と円: 交わる/接する/含む/離れる を二乗距離で厳密に
i128 d2  = dist2(c1.c, c2.c);
i128 sp  = (i128)(c1.r + c2.r) * (c1.r + c2.r);
i128 dm  = (i128)(c1.r - c2.r) * (c1.r - c2.r);
// d2 >= sp        -> 離れる（接する含む）
// d2 <= dm        -> 内包（内接含む）
```

`commonTangents` の本数決定、`ccInter` の交差判定はこの二乗比較に置き換えれば `commonTangents` 経由の eps 依存が消える。

### 3.3 どう「過程」から eps を消すか（まとめ）

| 残る実数 | 対応 |
|---|---|
| 交点座標 | 最後に `ld` で計算（過程では使わない） |
| 面積・距離 | `ld`（整数入力なら有理数/`i128` 比で厳密比較も可） |
| 角度（`atan2`） | 途中の分岐に使わない（`isconvex` の総回転角は winding number に置換） |
| 円の接点 | 値としてのみ。存在判定は二乗比較 |

`isconvex` の `atan2l` 総回転角チェックは、**winding number（整数の交差数え上げ）== ±1** に置き換えれば厳密化できる（自己交差する螺旋を弾く目的はそのまま達成）。

### 3.4 移行案（小さく安全に）

1. `Point` を型テンプレート化し、`Point<ll>`（整数）と `Point<ld>`（実数）を併設。既定は互換のため `ld`。
2. 判定中心の関数に整数オーバーロードを追加: `ccw`, `onSegment`, `segInter`, `lineInter`, `convex_hull`, `isconvex`, `isinPolygon`, `Polygon_cut`, `diamConvex`。
3. `EPS`/`eq`/`sign` は互換のため残すが、ドキュメントで「整数版では使わない」と明記。
4. verify（AOJ CGL / LC）を整数座標で回し、現行版と結果一致を確認。

---

## 4. 検証方法（回帰テスト）

今回の調査で使った「現行コード vs 厳密 `__int128` 実装」の総当たり比較を回帰テスト化する。

- `convex_hull` / `isinPolygon` / `ccw` / `segInter` を整数ランダム入力で比較（座標範囲 1e6 / 1e9 / 1e18、共線寄り分布を含む）。
- 現状の結果: R=1e6, 1e9 は一致、R=1e18 は不一致（`ld` の限界）。厳密版導入後は全範囲で一致するはず。
- verify は AOJ CGL（全て整数 or 小数 3〜4 桁）と LC（整数、|座標|≦1e9）を利用。

---

## 5. ICPC ライブラリとして追加したい幾何機能（#144 候補）

現在の Geometry は **2D の基本 + 円まわりがかなり充実 + 最小包含円/凸包/直径/最近点対**。一方で、ICPC の定番で欠けているものがいくつかある。

### 優先度 高

| 機能 | 理由 |
|---|---|
| **半平面交差 (half-plane intersection)** | 凸多角形の共通部分・線形計画・実行可能領域。ICPC 幾何の最重要欠落。 |
| **凸多角形の共通部分（面積）** | 半平面交差 or 回転カリパスで実現。多角形クリップの一般化。 |
| **点が凸多角形の内側か O(log n)** | 現行 `isinPolygon` は O(n)。クエリ多数で必須。 |
| **線分と円の交点** | 現行 `clInter` は直線。線分にクランプした版があると便利。 |
| **円の合併面積** | 円周ソート + 区間被覆。環状の定番。 |
| **厳密整数幾何 (`IPoint` + 述語)** | #133 と共通基盤。スケール・環境非依存。 |

### 優先度 中

| 機能 | 理由 |
|---|---|
| **Minkowski 和（凸）** | 凸多角形の距離・衝突判定。 |
| **多角形の重心 (centroid)** | 面積重み付き重心。 |
| **最小外接長方形 / 幅（回転カリパス）** | `diamConvex` の一般化。 |
| **3D 幾何一式** | `Point3D` は点演算のみ。`Plane`・点/直線-平面・直線間距離・`Sphere`・3D 凸包など。 |
| **角度ソート（`argCmp`）** | 極座標ソート。LC に `sort_points_by_argument` があり verify 可能。 |
| **Manhattan ⇄ Chebyshev 変換** | 45°回転。マンハッタン距離問題の定番。 |
| **線分と多角形の交差判定** | 障害物判定。 |

### 優先度 低 / 任意

| 機能 | 理由 |
|---|---|
| Delaunay 三角分割 / Voronoi | 高難度。需要は限定的。 |
| 一般（非凸）多角形の共通部分面積 | 分解が必要。 |
| Pick の定理 / 格子点数 | 数論寄り。 |
| 多角形の三角形分割 | 一部は半平面交差で代替可。 |

---

## 6. 提案する進め方

1. **基盤**: `IPoint`（`ll`）と厳密述語（`__int128`）を追加。既存 `Point` は互換維持。
2. **置換**: 判定中心の関数（`ccw` / `onSegment` / `segInter` / `lineInter` / `convex_hull` / `isconvex` / `isinPolygon` / `Polygon_cut`）を整数版で置き換え、`EPS` を過程から排除。
3. **円まわり**: 存在判定を二乗距離の厳密比較へ（`clInter` / `ccInter` / `commonTangents` / `CircCircInter`）。
4. **回帰テスト**: 本レポートの総当たり比較 + AOJ/LC verify。
5. **#144**: 上記基盤の上に **半平面交差** を最優先で追加。

---

## 付録: 調査で使った比較テスト（要約）

- 現行 `Geometry/*.cpp` と、`__int128` の厳密 `convex_hull` / `isinPolygon` を同一入力で比較。
- 座標範囲・共線寄り分布を変えて 2000 試行 × 複数範囲。
- 実行コマンド例: `g++ -std=c++20 -O2 -I <repo> test_eps.cpp -o test_eps && ./test_eps`
