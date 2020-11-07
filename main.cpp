#include <chrono>
#include <thread>
#include "LineIntersection.h"

int main()
{
    constexpr size_t WindowWidth = 800;
    constexpr size_t WindowHeight = 800;

    LineIntersection window(WindowWidth, WindowHeight, "Line Line Intersection Example");
    while(window.processEvents())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return 0;
}
