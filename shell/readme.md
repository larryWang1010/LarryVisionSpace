## 使用命令直接执行，而不用`./xxx`
将其当前目录加入`PATH`变量，然后给`.sh`创建软链接
```shell
export PATH="${PATH}:/home/larry/Documents/LearnSpace/LarryVisionSpace/shell"
ln -s test1.sh tt
```

