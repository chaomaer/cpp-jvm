# An Educational Java Virtual Machine

## 使用方法
准备工作
```
# 解压rt.jar到指定文件夹
cd ${dir-rt-extract} && jar -xvf rt.jar
```
```
# Clone a repo
$ git clone https://github.com/chaomaer/cpp-jvm
$ cd cpp-jvm

# Build cpp-jvm
$ mkdir build
$ cmake .. （如果是Mac系统，需要加-DAPPLE=1）
$ make

# 运行class文件
$ cd build/
$ ./cpp-jvm {dir-rt-extract} {path-of-class} ${name-of-class}
```

## 功能实现
- :white_check_mark: 加载class文件
- :white_check_mark: 字符串和数组
- :white_check_mark: 函数调用
- :white_check_mark: 类和对象
- :white_check_mark: 多线程
- :white_large_square: monitor支持
- :white_large_square: 垃圾回收GC
- :white_large_square: 多亲委派类加载
