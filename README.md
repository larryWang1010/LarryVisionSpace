# VisionSpace
goal:
1. To be a excellent enginner.

note:
1. record learnging experience about vision including vslam, computer vision, opencv, mathematic and programming etc.

Fighting!

# 目录架构
`vision space`大多存放短小，琐碎的工程或代码，因此，没有必要为每个项目，如`eigen`，`shell`等，单独建立一个工程，写 CMakeLists，造成代码的大量冗余，因此，采用**多级目录**的方式组织，所有的项目以**子目录**的形式在`vision space`目录下构建，顶层目录仅添加公共选项，不构建具体的 target，如果要添加项目使用`add_subdirectory`命令在子目录内构建 target。
## 使用
1. gtest 单元测试使用，子目录单独添加`test_main.cpp`程序，即可使用 gtest 框架；


## 代码要求
1. 功能或代码很少的，使用单元测试，不要单独构建一个 target；

todo 
1. 积累到一定时刻，公开该仓库。


# 参考资料
https://github.com/Ewenwan/MVision