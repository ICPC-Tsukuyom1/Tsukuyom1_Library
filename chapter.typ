#import "@preview/codelst:2.0.2": sourcefile, sourcecode

= Template

== template
#sourcefile(read("./template.cpp"), lang: "cpp")

== run.sh
#sourcefile(read("./run.sh"), lang: "sh")

#include "./Math/modint.typ"