# sh run.sh <hoge> -> <hoge>.cpp の実行
S=$1.cpp
O=$1.out
T=input.txt
g++ -x c++ -g -O2 -D _GLIBCXX_DEBUG -std=gnu++20 -Wall -static -o $O $S && ./$O < $T