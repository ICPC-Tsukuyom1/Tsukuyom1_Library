#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== manhattanMST
マンハッタン距離による最小全域木を求める。座標は整数であることを仮定する。
返り値は `{重み, u, v}` の配列（頂点数 $n$ に対し $n - 1$ 本）。
#sourcefile(read("../Geometry/manhattanMST.cpp"), lang: "cpp")
