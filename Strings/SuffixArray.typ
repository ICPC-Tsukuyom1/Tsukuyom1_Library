#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== Suffix Array
`sa[i]` : 辞書順で `i` 番目の suffix の開始 index 。
`lcp[i]` : 辞書順で `i` 番目と `i - 1` 番目の suffix の最長共通接頭辞の長さ。

長さ $n$ の文字列 `s` の相異なる部分文字列の個数は $n(n+1)/2 - sum "lcp"[i]$

#sourcefile(read("../Strings/SuffixArray.cpp"), lang: "cpp")
