#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== 実行環境関連

=== Linux

#sourcecode(```shell
# stack領域のメモリ制限回避
$ ulimit -s unlimited

# プロセスの利用リソースの確認
$ /usr/bin/time -v ./a.out

# 標準エラー出力のリダイレクト
$ ./a.out 2> /dev/null
```)

=== GDB/LLDB

#sourcecode(```shell
$ gdb ./a.out       # デバッガ起動

gdb> b a.cpp:50     # ブレークポイントの指定
gdb> i b            # ブレークポイント一覧の表示
gdb> d 3            # ブレークポイント削除
gdb> watch hoge     # グローバル変数の変更で停止
gdb> r < ./in.txt   # 標準入力を与えつつ実行
gdb> c              # 次のブレークポイントまで進む
gdb> n              # 1行進んで停止
gdb> s              # 行内で実行されている関数の中に進む
gdb> bt             # スタックトレース表示
gdb> i lo           # ローカル変数表示
gdb> l              # ソースコード表示
gdb> printf "%s",e  # 式を評価してprint
gdb> return 0       # 関数をreturn
```)

=== C++高速化

#sourcecode(```cpp
pragma GCC target("avx2")
pragma GCC optimize("O3")
pragma GCC optimize("unroll-loops")
```)
