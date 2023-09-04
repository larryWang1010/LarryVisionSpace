#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> v3;
    std::vector<int> v4;
    // 创建空的容器，capacity和size都为空
    printf("v1,v2,v3,v4 size     are: %ld,%ld,%ld,%ld \n", v1.size(), v2.size(), v3.size(), v4.size());
    printf("v1,v2,v3,v4 capacity are: %ld,%ld,%ld,%ld \n", v1.capacity(), v2.capacity(), v3.capacity(), v4.capacity());

    v2.push_back(99);
    printf("v2 size and capaciry are: %ld:%ld \n", v2.size(), v2.capacity());

    // 第1次改变
    v1.resize(100);
    v2.resize(100);
    v2.push_back(66);  // 添加一个元素

    v3.reserve(100);
    v4.reserve(100);

    printf("v1 elements: %d,%d,%d \n", v1.at(5), v1.at(15), v1.at(45));  // 查看resize之后元素，可知默认为0

    printf("v1,v2,v3,v4 size     are: %ld,%ld,%ld,%ld \n", v1.size(), v2.size(), v3.size(), v4.size());
    printf("v1,v2,v3,v4 capacity are: %ld,%ld,%ld,%ld \n", v1.capacity(), v2.capacity(), v3.capacity(), v4.capacity());
    // 第2次改变
    v1.resize(200);
    v2.reserve(200);
    v3.reserve(200);
    v4.resize(200);
    printf("v1,v2,v3,v4 size     are: %ld,%ld,%ld,%ld \n", v1.size(), v2.size(), v3.size(), v4.size());
    printf("v1,v2,v3,v4 capacity are: %ld,%ld,%ld,%ld \n", v1.capacity(), v2.capacity(), v3.capacity(), v4.capacity());
}
// 参考
// https://blog.csdn.net/amusi1994/article/details/81106455
