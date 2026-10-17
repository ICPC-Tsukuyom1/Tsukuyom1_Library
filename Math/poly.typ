#import "@preview/codelst:2.0.2": sourcefile, sourcecode


== poly

modint を係数とする多項式。加減乗算・除算 ($op("/")$, $op("%")$ と `div_mod`)・シフト・評価・微分積分・形式的逆元・テイラーシフトを提供する。

#sourcefile(read("poly.cpp"), lang: "cpp")
