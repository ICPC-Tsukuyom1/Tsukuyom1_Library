# トポロジカルソート
[実装](https://github.com/Oxojo/Oxojo-Library/blob/main/Graph/topological.cpp)
## なにこれ
トポロジカルソートをします<br>
DAG について、ある頂点の子が全て自身より後に来るように頂点を並べる

## 必要なライブラリ
[Graph](https://oxojo.github.io/Oxojo-Library/Graph/Graph)

## 使い方
```
p = topological_sort(G)
```
p は確かソートされた頂点を順番に格納した配列になるはず...
