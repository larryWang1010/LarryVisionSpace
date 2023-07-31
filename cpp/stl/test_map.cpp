#include <iostream>
#include <map>
#include <string>
int main() {
    std::map<char, int> mymap;
    // * 插入
    // 插入单个值
    mymap.insert(std::pair<char, int>('a', 100));
    mymap.insert(std::pair<char, int>('z', 200));
    // 返回插入位置以及是否插入成功
    std::pair<std::map<char, int>::iterator, bool> ret;  // 注意返回值的数据结构
    ret = mymap.insert(std::pair<char, int>('z', 500));
    if (ret.second == false) {
        std::cout << "Element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }
    //指定位置插入
    std::map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, std::pair<char, int>('b', 300));  //效率更高
    mymap.insert(it, std::pair<char, int>('c', 400));  //效率非最高 有什么区别吗？
    //范围多值插入
    std::map<char, int> anothermap;
    anothermap.insert(mymap.begin(), mymap.find('c'));
    // 列表形式插入
    anothermap.insert({{'d', 100}, {'e', 200}});
    // * 修改 value
    std::map<char, int>::iterator iter2;
    iter2 = mymap.find('a');
    if (iter2 != mymap.end()) iter2->second = 101;
    mymap['b'] = 301;
    // * 遍历 1. 正向迭代器，反向迭代器
    std::map<char, int>::const_iterator iter1;
    std::cout << "Elements is: ";
    for (iter1 = mymap.cbegin(); iter1 != mymap.cend(); ++iter1)
        std::cout << "[" << iter1->first << " " << iter1->second << "] ";
    std::cout << std::endl;
    // * 查找
    std::map<char, int>::iterator iter;
    iter = mymap.find('a');
    if (iter != mymap.end()) std::cout << "Find " << iter->first << "=" << iter->second << std::endl;
    return 0;
}
