#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== furthestNeighbors
反時計回りの凸多角形の各頂点について、最も距離が大きい頂点の番号を求める。
距離行列が totally monotone であることを使って $O(n log n)$。
#sourcefile(read("../Geometry/furthestNeighbors.cpp"), lang: "cpp")
