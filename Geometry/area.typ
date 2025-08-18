#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Area

*なにこれ*

多角形の面積を求めます #strike[凸多角形でない場合、バグるかもしれないです] ←凸でなくてもバグらないことを確認しました

*必要なライブラリ*
- Geometry/template
- Geometry/dot_cross

*使い方*
```
s = Area(S);
```
引数は Polygon 型

*実装*

#sourcefile(read("../Geometry/area.cpp"), lang: "cpp")

*Verify*

AOJ_CGL_3_A

#sourcecode[```cpp
void solve() {
  ll N; cin >> N;
  Polygon S(N);
  for (ll i = 0; i < N; i++) {
    cin >> S[i].x >> S[i].y;
  }
  cout << fixed << setprecision(1) << Area(S) << endl;
}
```]