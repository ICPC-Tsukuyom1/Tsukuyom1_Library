#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== KMP
(正確には MP)

`pi(s)` → `p[i]` : `s[0:i-1]` の接頭辞と接尾辞が最長で何文字等しいか

`match(s, pat)` → s 内で pat が現れる index をすべて返す


#sourcefile(read("../Strings/KMP.cpp"), lang: "cpp")
