#import "@preview/codelst:2.0.2": sourcefile, sourcecode

= Template

== setup

- template.cpp, i/o setup, run.sh を写経する
- dist, input ディレクトリを作成する
- input の中に `a.txt, b.txt, ...` を作成
- `a.cpp, b.cpp, ...` を作成

== template
#sourcefile(read("./template.cpp"), lang: "cpp")

== i/o setup
```
ios::sync_with_stdio(false);
cin.tie(nullptr);
cout << fixed << setprecision(12);
```

== run.sh
#sourcefile(read("./run.sh"), lang: "sh")

#include "./Math/modint.typ"