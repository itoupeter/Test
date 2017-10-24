
#include <chrono>
#include <thread>
#include <iostream>

int main()
{
    auto begin = std::chrono::high_resolution_clock::now();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    
    return 0;
}