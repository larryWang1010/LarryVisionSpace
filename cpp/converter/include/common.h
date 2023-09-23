#include <chrono>
typedef std::chrono::system_clock sys_clk_t;
typedef std::chrono::steady_clock steady_clk_t;

typedef std::chrono::system_clock::time_point sys_time_t;
typedef std::chrono::steady_clock::time_point steady_time_t;
// default double
typedef std::chrono::duration<double, std::milli> dura_ms_t;  // ms

typedef std::chrono::duration<float, std::milli> fdura_ms_t;