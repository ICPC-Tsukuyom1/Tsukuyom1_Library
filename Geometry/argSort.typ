#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== argSort
点を偏角で反時計回りにソートする。半直線 $x <= 0, y = 0$ を始点とする。
同じ偏角の点同士の順序は不定。
#sourcefile(read("../Geometry/argSort.cpp"), lang: "cpp")
