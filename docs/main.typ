#import "@preview/codelst:2.0.2": sourcefile, sourcecode

// レイアウト設定

#set page(
  flipped: true,
  columns: 3,
  margin: (
    top: 24pt,
    bottom: 16pt,
    left: 16pt,
    right: 16pt
  ),
  header: context(
    [
      #h(1fr)
      Tsukuyom1 Library
      #h(1fr)
      #counter(page).display("1")
    ]
  )
)

#set text(
  size: 9pt,
  font: "Noto Sans CJK JP",
)

#show heading.where(level: 1): text.with(fill: white)

#show heading.where(level: 1): block.with(
  fill: luma(0%),
  inset: 4pt
)
#show heading: set block(above: 8pt, below: 8pt)

#show heading.where(level: 2): block.with(
  stroke: black,
  inset: 2pt
)

// 内容

#outline(
  title: "TOC",
)

= Template

#sourcefile(read("../template.cpp"), lang: "cpp")

= Geometry

== Template

#sourcefile(read("../geometry/template.cpp"), lang: "cpp")

#include "../geometry/area.typ"

#include "../Geometry/ccw.typ"