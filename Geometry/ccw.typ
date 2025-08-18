#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== CCW

*なにこれ*

3点の位置関係を示す

*必要なライブラリ*

- Geometry/template
- Geometry/dot_cross

*使い方*

```cpp
check = ccw(a, b, c);
```

返り値は
- `1` : a, b, c の順に反時計回りになるようになってる
- `-1` : a, b, c の順に時計回りになるようになってる
- `2` : c, a, b の順で同一直線上にある
- `-2` : a, b, c の順で同一直線上にある
- `0` : a, c, b の順で同一直線状にある
のいずれか。

*実装*

#sourcefile(read("../geometry/ccw.cpp"), lang: "cpp")

