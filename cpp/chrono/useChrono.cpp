#include <chrono>
#include <iostream>

typedef std::chrono::system_clock system_clk_t;
typedef std::chrono::steady_clock steady_clk_t;

typedef std::chrono::system_clock::time_point system_time_t;
typedef std::chrono::steady_clock::time_point steady_time_t;
typedef std::chrono::duration<double> dDura_t;
typedef std::chrono::duration<float> fDura_t;

long fibonacci(unsigned n) {
    if (n < 2) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
// unix时间，即1970-1-1到当前的时间，单位为s
int main() {
    system_time_t system_time = system_clk_t::now();
    // 计算目前的unix时间，19位（即纳秒 ns）
    std::cout << "Timestamp is: " << system_time.time_since_epoch().count() << std::endl;

    std::time_t sys_time1 = system_clk_t::to_time_t(system_time);
    // ! 计算程序运行时间，使用steady_clock
    steady_time_t timeStart = steady_clk_t::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    steady_time_t timeStart = steady_clk_t::now();
    dDura_t timeFibonacci = timeStart - timeStart;
    std::cout << "elapsed time: " << timeFibonacci.count() << "s\n";

    // 目的：获取时刻，计算持续时间（各个单位之间的转换）
}