
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
#include <boost/range/irange.hpp>

int main()
{
    std::vector<std::thread> threads;

    const int c_numThreads = 10;
    std::atomic_bool canStart = false;

    for (auto i : boost::irange(0, c_numThreads))
    {
        threads.emplace_back([=, &canStart]()
        {
            while (!canStart.load()) {}

            for (int j : boost::irange(0, 100))
            {
                std::cout << i;
            }
        });
    }

    canStart = true;

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}