#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== halfPlaneInter
各直線の左側の半平面の共通部分を求める（半平面交差）。
共通部分が空のときは空の多角形を返す。半平面全体が有界になるように直線を与えることを想定している。
#sourcefile(read("../Geometry/halfPlaneInter.cpp"), lang: "cpp")
