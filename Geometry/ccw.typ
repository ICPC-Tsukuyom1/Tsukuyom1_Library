#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== CCW

返り値が
- `1` : a, b, c の順に反時計回り
- `-1` : a, b, c の順に時計回り
- `2` : c, a, b の順で同一直線上
- `-2` : a, b, c の順で同一直線上
- `0` : a, c, b の順で同一直線上

#sourcefile(read("../Geometry/ccw.cpp"), lang: "cpp")

