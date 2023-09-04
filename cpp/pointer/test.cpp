#include <iostream>
using namespace std;
class A {
   public:
    void Func(void) { cout << "Func of class A" << endl; }
};
class B {
   public:
    A* p;
    void Test(void) {
        A a;
        p = &a;  // 注意 a 的生命期 ，只在这个函数Test中，而不是整个class B
        cout << "Address of p in Test  " << p << endl;
    }
    void Test1() {
        // p是“野指针”，函数结束时a将被析构，所以在函数外使用指针p指向的内存空间已经被释放了，所以p已经是野指针了,该指针指向的内存为垃圾内存
        p->Func();
        cout << "Address of p in Test1 " << p << endl;  // 可以看到，p依旧指向Test函数中的地址，但A对象已经析构了
    }
};

int main() {
    A* a = nullptr;
    cout << "Address of a " << a << endl;  // 会出现，每次运行程序，指针a的地址都是不以一样的
    B test;
    test.Test();
    test.Test1();
}
