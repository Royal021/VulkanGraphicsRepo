#include "timeutil.h"
#include <chrono>
#include <thread>
#include <cstdint>

static auto start = std::chrono::steady_clock::now();

double timeutil::time_sec()
{
    auto n = std::chrono::steady_clock::now();
    std::int64_t usec = std::chrono::duration_cast<std::chrono::microseconds>(n-start).count();
    return 1E-6 * double(usec);
}

void timeutil::sleep(double duration)
{
    std::this_thread::sleep_for(std::chrono::microseconds( (unsigned long)(duration*1'000'000)));
}
