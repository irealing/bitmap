## 使用C语言实现的Python Bitmap模块

* 包含C语言和Python两种实现
* 分块加载，每块使用1MiB内存

### 示例

```python
from bitmap import PyBitmap

if __name__ == "__main__":
    bm = PyBitmap(2*8*1024*1024)
    success, failed = 0, 0
    for x in range(2*8*1024*1024+10):
        bm.add(x)
        if bm.has(x):
            success += 1
        else:
            failed += 1
    print(f"success = {success} ;failed = {failed}")

```

### 构建C动态链接库

```shell
$ cmake . && make
```

@author:[Memory_Leak](mailto:irealing@163.com)
