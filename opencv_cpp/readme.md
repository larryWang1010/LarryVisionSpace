<!--
 * @Description: demo 使用
 * @Author: larry.wang
 * @Date: 2023-07-27 13:59:37
-->
## 编译
统一编译，根据需要注释`CMakeLists.txt`中不使用的 test 即可
```sh
cd build
rm -rf *
cmake ..
make -j
```
## 运行

### opencv test demo
运行
```sh
./bin/test_orb -d ./data/3.png
```

REFERENCE
https://www.cnblogs.com/zyly/p/9646201.html


### test_orb
运行
```sh
./bin/test_orb -d ./data/1403636859301666560.png -f /home/larry/Documents/LearnSpace/LarryVisionSpace/opencv/script/EuRoC.yaml
```