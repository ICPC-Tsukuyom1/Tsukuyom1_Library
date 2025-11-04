#import "@preview/codelst:2.0.2": sourcefile, sourcecode

== タイマー

=== `timer`

精度は10msほど

#sourcecode(```cpp
clock_t start = clock();
hoge();
clock_t end = clock();
ll ms = (end - start) * 1000 / CLOCKS_PER_SEC;
```)

=== `chrono`

精度は1msほど

#sourcecode(```cpp
auto start = chrono::system_clock::now();
// 計測したい処理を書く
auto finish = chrono::system_clock::now();

ll ms = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
```)
