// 現行 Geometry（EPS 依存の ld 実装）と、厳密 __int128 実装を総当たり比較する調査用テスト。
// 使い方: g++ -std=c++20 -O2 research/geometry_exactness_compare.cpp -o compare && ./compare
//
// 期待される観察（2026-10 時点の現行実装）:
//   convex_hull : R=1e6, 1e9 では不一致 0 / R=1e18 では不一致あり（ld の仮数限界）
//   isinPolygon : R=1e9 では不一致 0 / R=1e18 で境界を内側と誤判定
//   ccw / convex_hull : スケールを 1e-4 以下にすると本物の CCW・頂点が退化扱い
// 厳密実装（IPoint）へ置き換えた後は、どの範囲でも不一致 0 になるのが目標。

#include "../template.cpp"
#include "../Geometry/Point.cpp"
#include "../Geometry/ccw.cpp"
#include "../Geometry/onSegment.cpp"
#include "../Geometry/convex_hull.cpp"
#include "../Geometry/isinpolygon.cpp"

#include <random>

using i128 = __int128_t;

struct IP {
  ll x, y;
};
static i128 cr3(const IP& a, const IP& b, const IP& c) {
  return (i128)(b.x - a.x) * (c.y - a.y) - (i128)(b.y - a.y) * (c.x - a.x);
}

// 厳密 convex hull（単調鎖法）。strict=true => 共線点を落とす（ライブラリと同じ）
static vec<IP> exact_hull(vec<IP> p, bool strict) {
  sort(p.begin(), p.end(),
       [](const IP& a, const IP& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
  p.erase(unique(p.begin(), p.end(),
                 [](const IP& a, const IP& b) { return a.x == b.x && a.y == b.y; }),
          p.end());
  ll n = sz(p);
  if (n <= 2) return p;
  vec<IP> h(2 * n);
  ll k = 0;
  auto bad = [&](ll i) {
    i128 c = cr3(h[k - 2], h[k - 1], p[i]);
    return strict ? c <= 0 : c < 0;
  };
  for (ll i = 0; i < n; h[k++] = p[i++])
    while (k >= 2 && bad(i)) --k;
  for (ll i = n - 2, t = k + 1; i >= 0; h[k++] = p[i--])
    while (k >= t && bad(i)) --k;
  h.resize(k - 1);
  return h;
}

static string key(const vec<IP>& v) {
  vec<pair<ll, ll>> q;
  for (auto& p : v) q.push_back({p.x, p.y});
  sort(all(q));
  string s;
  for (auto& p : q) s += "(" + to_string(p.first) + "," + to_string(p.second) + ")";
  return s;
}
static string lkey(const Polygon& v) {
  vec<pair<ll, ll>> q;
  for (auto& p : v) q.push_back({(ll)p.x, (ll)p.y});
  sort(all(q));
  string s;
  for (auto& p : q) s += "(" + to_string(p.first) + "," + to_string(p.second) + ")";
  return s;
}

// 厳密 point in polygon（1=境界 / 2=内側 / 0=外側）
static int exact_inpoly(const IP& a, const vec<IP>& poly) {
  ll n = sz(poly);
  rep(i, n) {
    IP p = poly[i], q = poly[(i + 1) % n];
    if (cr3(p, q, a) == 0 && min(p.x, q.x) <= a.x && a.x <= max(p.x, q.x) &&
        min(p.y, q.y) <= a.y && a.y <= max(p.y, q.y))
      return 1;
  }
  bool in = false;
  rep(i, n) {
    IP p = poly[i], q = poly[(i + 1) % n];
    if ((p.y > a.y) != (q.y > a.y)) {
      i128 num = (i128)(a.y - p.y) * (q.x - p.x) - (i128)(a.x - p.x) * (q.y - p.y);
      bool right = (q.y > p.y) ? (num > 0) : (num < 0);
      if (right) in = !in;
    }
  }
  return in ? 2 : 0;
}

int main() {
  mt19937_64 rng(12345);

  // (1) convex_hull: 現行(eps/ld) vs 厳密, 整数座標
  for (ll R : {(ll)1000000, (ll)1000000000, (ll)1000000000000000000LL}) {
    ll trials = 2000, mismatch = 0;
    string example;
    rep(t, trials) {
      ll n = 3 + rng() % 20;
      vec<IP> p(n);
      rep(i, n) {
        if (t % 2 == 0) {
          p[i].x = (ll)(rng() % (2 * (unsigned long long)R + 1)) - R;
          p[i].y = (ll)(rng() % (2 * (unsigned long long)R + 1)) - R;
        } else {
          ll k = (ll)(rng() % 7);
          p[i].x = k * (R / 7) + (ll)(rng() % 3) - 1;
          p[i].y = k * (R / 7) + (ll)(rng() % 3) - 1;
        }
      }
      Polygon lp(n);
      rep(i, n) { lp[i].x = (ld)p[i].x; lp[i].y = (ld)p[i].y; }
      Polygon lh = convex_hull(lp, true);
      vec<IP> eh = exact_hull(p, true);
      string a = lkey(lh), b = key(eh);
      if (a != b) {
        mismatch++;
        if (example.empty()) {
          example = "n=" + to_string(n);
          for (auto& q : p) example += " (" + to_string(q.x) + "," + to_string(q.y) + ")";
          example += "\n   lib=" + a + "\n   exact=" + b;
        }
      }
    }
    printf("[convex_hull str=true] R=%lld : %lld/%lld mismatch\n", R, mismatch, trials);
    if (!example.empty()) printf("   first: %s\n", example.c_str());
  }

  // (2) isinPolygon（整数座標）vs 厳密
  for (ll R : {(ll)1000000000, (ll)1000000000000000000LL}) {
    ll trials = 2000, mismatch = 0;
    string example;
    rep(t, trials) {
      ll n = 3 + rng() % 12;
      vec<IP> pts(n);
      rep(i, n) {
        pts[i].x = (ll)(rng() % (2 * (unsigned long long)R + 1)) - R;
        pts[i].y = (ll)(rng() % (2 * (unsigned long long)R + 1)) - R;
      }
      vec<IP> poly = exact_hull(pts, true);
      if (sz(poly) < 3) continue;
      Polygon lp(sz(poly));
      rep(i, sz(poly)) { lp[i].x = (ld)poly[i].x; lp[i].y = (ld)poly[i].y; }
      rep(k, 8) {
        IP q;
        if (k < 5) {
          q.x = (ll)(rng() % (2 * (unsigned long long)R + 1)) - R;
          q.y = (ll)(rng() % (2 * (unsigned long long)R + 1)) - R;
        } else {
          ll e = rng() % sz(poly), e2 = (e + 1) % sz(poly);
          IP A = poly[e], B = poly[e2];
          ll num = 1 + rng() % 5, den = 6;
          q.x = (A.x * (den - num) + B.x * num) / den;
          q.y = (A.y * (den - num) + B.y * num) / den;
        }
        Point pq((ld)q.x, (ld)q.y);
        int lib = isinPolygon(pq, lp);
        int ex = exact_inpoly(q, poly);
        if (lib != ex) {
          mismatch++;
          if (example.empty()) {
            example = "q=(" + to_string(q.x) + "," + to_string(q.y) + ")  lib=" +
                      to_string(lib) + " exact=" + to_string(ex);
            example += "\n   poly=";
            for (auto& v : poly) example += "(" + to_string(v.x) + "," + to_string(v.y) + ")";
          }
        }
      }
    }
    printf("[isinPolygon] R=%lld : %lld mismatches (queries)\n", R, mismatch);
    if (!example.empty()) printf("   first: %s\n", example.c_str());
  }

  // (3) スケール依存
  {
    ld s = 1.0L;
    for (int e = 0; e <= 15; e++) {
      Point A(0, 0), B(s, 0), C(0, s * 1e-3L);
      int r = ccw(A, B, C);
      printf("[ccw scale] s=1e%-3d -> %s\n", -e,
             r == COUNTER_CLOCKWISE ? "CCW" : (r == ON_SEGMENT ? "ON_SEGMENT" : "other"));
      s /= 10;
    }
    Polygon t{Point(0, 0), Point(1e-6L, 0), Point(0, 1e-6L)};
    Polygon h = convex_hull(t, true);
    printf("[convex_hull tiny] vertices: %lld (exact would be 3)\n", sz(h));
  }
  return 0;
}
