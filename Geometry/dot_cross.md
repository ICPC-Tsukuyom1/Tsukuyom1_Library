# 内積・外積

## なにこれ
内積と外積です

## 必要なライブラリ
[template](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/template.md)

## 使い方
### 内積
```
d = dot(a, b);
```

### 外積
```
c = cross(a, b);
```

## 実装
[dot_cross.cpp](https://github.com/Oxojo/Oxojo-Library/blob/main/Geometry/dot_cross.cpp)
```cpp
ld dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}
ld cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}
```
