#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 幾何

=== 三角形

辺の長さを $a, b, c$ として、$display(p=(a+b+c)/2)$ とすると、面積 $A = sqrt(p(p-a)(p-b)(p-c))$、外接円半径 $display(R = (a b c)/4A)$、内接円半径 $display(r=A/p)$

正弦定理 : $display((sin alpha)/a = (sin beta)/b = (sin gamma)/c = 1/(2R))$

余弦定理 : $a^2 = b^2 + c^2 - 2b c cos alpha$

正接定理 : $display((a+b)/(a-b)=(tan (alpha + beta)/2)/(tan (alpha - beta)/2))$