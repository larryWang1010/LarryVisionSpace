#include <chrono>
#include <iostream>
// clock
typedef std::chrono::system_clock sys_clk_t;
typedef std::chrono::steady_clock std_clk_t;
// timepoint
typedef std::chrono::system_clock::time_point sys_time_t;
typedef std::chrono::steady_clock::time_point std_time_t;
// duration (default double)
typedef std::chrono::duration<double, std::milli> duration_ms_t;
typedef std::chrono::duration<double, std::micro> duration_us_t;
typedef std::chrono::duration<double, std::nano> duration_ns_t;
typedef std::chrono::duration<float, std::milli> fduration_ms_t;
typedef std::chrono::duration<float, std::micro> fduration_us_t;
typedef std::chrono::duration<float, std::nano> fduration_ns_t;
