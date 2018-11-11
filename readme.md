# 四种全排列算法实现

## 代码说明

按照课堂上介绍的四种全排列算法，分别求出83674521之前第2018个排列

  - lexicographical.h 字典序
  - increase.h 递增进位制
  - decrease.h 递减进位制
  - sjt.h SJT算法

## 编译运行

```make
make permutation
```

会看到输出：
```bash
g++ permutation.cpp -o permutation -std=c++11
[+] Run example:
###########################
./permutation 2018 <init.txt
Lex init perm: 8 3 6 7 4 5 2 1
Lex prev 2018: 8 1 2 3 6 5 7 4

Inc init perm: 8 3 6 7 4 5 2 1
Inc prev 2018: 8 6 2 5 4 3 7 1

Dec init perm: 8 3 6 7 4 5 2 1
Dec prev 2018: 3 6 8 7 2 4 5 1

SJT init perm: 8 3 6 7 4 5 2 1
SJT prev 2018: 4 8 7 6 3 2 5 1
```

permutation 用法：permutation **num** < init.txt
其中 init.txt 中是初始排列 8 3 6 7 4 5 2 1。格式见 init.txt
```
./permutation 2018 <init.txt
```

## 测试

算法运行效率测试对比
```
make time_test
```

算法正确性测试
```
make test
```

