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
  weight: "thin",
  font: "Noto Sans CJK JP",
)

#show heading.where(level: 1): text.with(fill: white)

#show heading.where(level: 1): block.with(
  above: 8pt,
  below: 4pt,
  fill: luma(0%),
  inset: 4pt
)

#show heading.where(level: 2): underline
#show heading.where(level: 2): text.with(
  weight: "semibold"
)
#show heading.where(level: 2): block.with(
  above: 8pt
)

// 内容

#outline(
  title: "TOC",
)

#include "../chapter.typ"
#include "../Geometry/chapter.typ"
#include "../Graph/chapter.typ"
#include "../Math/chapter.typ"
#include "../Structure/chapter.typ"
