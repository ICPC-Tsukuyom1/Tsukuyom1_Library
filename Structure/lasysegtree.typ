#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Lasy Segment Tree

初期状態ではRange Affine Range Sumの例が実装されているので、必要に応じてdefine部分を変更してください。
なおDynamic Lasy Segment Treeとして実装されているので、構築 $O(1)$ 、クエリ $O(log N)$ です。(N~10^18でも動作します)

#sourcefile(read("../Structure/lasysegtree.cpp"), lang: "cpp")