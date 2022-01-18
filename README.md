# 有损图像压缩算法

Run

```sh
make build
cd build&&cmake ../&&cmake --build .&&cd ..&&./build/OpenCV_learn
```

## 算法

删除每一个像素(24位)每个RGB值的最后一位(降低对比度).

## 结果

|压缩前|压缩后|
|---|---|
|179.1kb|29.4kb|

![example.png](image/example.png)

B 原图, C 压缩后, C2 直接内存数据复原, uncompress 存储成 jpg 文件后再复原.

## 缺陷

1. 色域会有损失
2. 存储成 jpg 文件后再复原数据不正确(*)
