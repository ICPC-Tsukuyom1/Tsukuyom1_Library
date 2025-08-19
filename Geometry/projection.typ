#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== Projection
#table(
  columns: (auto, auto),
  inset: 6pt,
  align: horizon,
  table.header(
    [reflect], [返り値],
  ),
  "true", "p から S へ下した垂線の足",
  "false", "S に関して p と対称な点",
)
#sourcefile(read("../Geometry/projection.cpp"), lang: "cpp")